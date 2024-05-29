#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>

double f(double x) {
    return 4.0 / (x * x + 1);
}

double compute_integral(double start, double end, double width) {
    double area = 0.0;
    for (double x = start; x < end; x += width) {
        area += f(x) * width;
    }
    return area;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <width> <num_processes>\n", argv[0]);
        return 1;
    }

    double width = atof(argv[1]);
    int num_processes = atoi(argv[2]);
    int pfd[num_processes][2];
    pid_t pid;
    double start, end, partial_sum, total_sum = 0.0;
    double range = 1.0;
    double segment_length = range / num_processes;

    clock_t start_time, end_time;
    start_time = clock();

    for (int i = 0; i < num_processes; i++) {
        if (pipe(pfd[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (pid == 0) {
            close(pfd[i][0]);
            start = i * segment_length;
            end = start + segment_length;
            partial_sum = compute_integral(start, end, width);
            write(pfd[i][1], &partial_sum, sizeof(double));
            close(pfd[i][1]);
            exit(EXIT_SUCCESS);
        } else { 
            close(pfd[i][1]);
        }
    }

    for (int i = 0; i < num_processes; i++) {
        read(pfd[i][0], &partial_sum, sizeof(double));
        total_sum += partial_sum;
        close(pfd[i][0]);
        wait(NULL);
    }

    end_time = clock();
    double time_spent = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    printf("Całkowita wartość całki: %f\n", total_sum);
    printf("Czas wykonania: %f sekund\n", time_spent);

    FILE *file = fopen("report.txt", "a");
    fprintf(file, "Szerokość: %f, Procesy: %d, Czas: %f sekund, Wynik: %f\n",
            width, num_processes, time_spent, total_sum);
    fclose(file);

    return 0;
}
