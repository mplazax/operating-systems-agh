#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <unistd.h>
#include <time.h>

#define MAX_PRINT_JOBS 10
#define CHARS_IN_JOB 10

struct print_job {
    char text[CHARS_IN_JOB + 1];
};

struct print_queue {
    struct print_job jobs[MAX_PRINT_JOBS];
    int head;
    int tail;
    int count;
};

int set_semvalue(int sem_id, int value) {
    union  semun {
        int val;
        struct semid_ds *buf;
        unsigned short *array;
    } arg;
    arg.val = value;
    return semctl(sem_id, 0, SETVAL, arg);
}

void semaphore_p(int sem_id) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = -1; // P()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        perror("semaphore_p failed");
        exit(1);
    }
}

void semaphore_v(int sem_id) {
    struct sembuf sem_b;
    sem_b.sem_num = 0;
    sem_b.sem_op = 1; // V()
    sem_b.sem_flg = SEM_UNDO;
    if (semop(sem_id, &sem_b, 1) == -1) {
        perror("semaphore_v failed");
        exit(1);
    }
}

void print_text(const char *text) {
    for (int i = 0; i < CHARS_IN_JOB; i++) {
        printf("%c", text[i]);
        fflush(stdout);
        sleep(1);
    }
    printf("\n");
}

void printer_process(int shm_id, int sem_queue, int sem_empty, int sem_full) {
    struct print_queue *queue = (struct print_queue *)shmat(shm_id, NULL, 0);

    while (1) {
        semaphore_p(sem_full);
        semaphore_p(sem_queue);

        struct print_job job = queue->jobs[queue->head];
        queue->head = (queue->head + 1) % MAX_PRINT_JOBS;
        queue->count--;

        semaphore_v(sem_queue);
        semaphore_v(sem_empty);

        print_text(job.text);
    }
}

void user_process(int shm_id, int sem_queue, int sem_empty, int sem_full) {
    struct print_queue *queue = (struct print_queue *)shmat(shm_id, NULL, 0);
    srand(time(NULL) ^ (getpid()<<16));

    while (1) {
        char text[CHARS_IN_JOB + 1];
        for (int i = 0; i < CHARS_IN_JOB; i++) {
            text[i] = 'a' + rand() % 26;
        }
        text[CHARS_IN_JOB] = '\0';

        semaphore_p(sem_empty);
        semaphore_p(sem_queue);

        queue->jobs[queue->tail] = (struct print_job){{0}};
        strcpy(queue->jobs[queue->tail].text, text);
        queue->tail = (queue->tail + 1) % MAX_PRINT_JOBS;
        queue->count++;

        semaphore_v(sem_queue);
        semaphore_v(sem_full);

        sleep(rand() % 3 + 1);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Usage: ./print_system <m value> <n value>");
        return EXIT_FAILURE;
    }
    int m = atoi(argv[1]);
    int n = atoi(argv[2]);

    int shm_id = shmget(IPC_PRIVATE, sizeof(struct print_queue), 0666 | IPC_CREAT);
    struct print_queue *queue = (struct print_queue *)shmat(shm_id, NULL, 0);
    queue->head = 0;
    queue->tail = 0;
    queue->count = 0;

    int sem_queue = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int sem_empty = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);
    int sem_full = semget(IPC_PRIVATE, 1, 0666 | IPC_CREAT);

    set_semvalue(sem_queue, 1);
    set_semvalue(sem_empty, MAX_PRINT_JOBS);
    set_semvalue(sem_full, 0);

    pid_t p;

    for (int i = 0; i < n + m; i++) {
        p = fork();
        if (p == 0 && i < m) {
            printer_process(shm_id, sem_queue, sem_empty, sem_full);
        } else if (p == 0 && i >= m) {
            user_process(shm_id, sem_queue, sem_empty, sem_full);
        } else if (p == -1) {
            perror("fork failed");
        }
    }

    for (int i = 0; i < n + m; i++) {
        wait(NULL);
    }

    semctl(sem_queue, 0, IPC_RMID);
    semctl(sem_empty, 0, IPC_RMID);
    semctl(sem_full, 0, IPC_RMID);
    shmctl(shm_id, IPC_RMID, NULL);

    return EXIT_SUCCESS;
}
