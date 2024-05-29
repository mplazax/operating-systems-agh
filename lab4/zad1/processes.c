#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int argc, char *argv[]) {

    if (argc != 2) {
        perror("Nalezy podac liczbe procesow potomnych\n");
        return 1;
    }

    int n_of_proc = atoi(argv[1]);

    for(int i = 0; i < n_of_proc; i++) {
        pid_t pid = fork();

        if(pid == 0) {


            printf("Child process pid %d\n", getpid());
            printf("Parent process pid %d\n", getppid());

            exit(0);
        } else if (pid < 0) {
            perror("Blad tworzenia procesu\n");
            exit(0);
        }
    }

    while(wait(NULL) > 0);

    printf("Liczba procesow potomnych: %d\n", n_of_proc);

    return 0;
}
