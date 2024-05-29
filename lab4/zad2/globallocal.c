#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int global = 0;

int main(int argc, char *argv[]) {
    if (argc != 2) {
        perror("Nalezy wpisać ściezkę katalogu\n");
        return 1;
    }

    printf("Nazwa programu: %s\n", argv[0]);

    int local = 0;
    pid_t pid = fork();

    if (pid < 0) {
        perror("Błąd przy wywoływaniu nowego procesu (pid < 0)\n");
        return 1;

    } else if (pid == 0) {
        global++;
        local++;

        printf("child process\n");
        printf("child pid = %d, parent pid = %d \n", getpid(), getppid());
        printf("child's local = %d, child's global = %d \n", local, global);

        exit(execl("/bin/ls", "ls", "-l", argv[1], NULL));
    }

    int status;

    wait(&status);

    int child_exit_code = WEXITSTATUS(status);

    printf("parent process\n");
    printf("parent pid = %d, child pid = %d \n", getpid(), pid);
    printf("Child exit code: %d \n", child_exit_code);
    printf("parent's local = %d, parent's global = %d \n", local, global);

    return 0;
}
