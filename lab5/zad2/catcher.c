#define _XOPEN_SOURCE 700 

#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>
#include <stdlib.h>


volatile int mode_changes = 0;
volatile int mode = -1;

void handle_mode(int new_mode) {
    mode_changes++;
    if (new_mode == 3) {
        printf("Exiting catcher\n");
    }
}



void handle_SIGUSR1(int signo, siginfo_t *info, void* extra) {
    int new_mode = info->si_int;
    
    printf("Recieved status %d from %d", new_mode, info->si_pid);
    mode_changes++;
    if (new_mode == 1) {
        for (int i = 1; i <= 100; i++){
            printf("%i, ", i);
        }
        printf("\n");
        kill(info->si_pid, SIGUSR1);
    } else if (new_mode == 2) {
        printf("Mode changes so far: %d\n", mode_changes);
        kill(info->si_pid, SIGUSR1);
    } else if (new_mode == 3) {
        printf("Exiting catcher\n");
        kill(info->si_pid, SIGUSR1);
        exit(0);
    }
}


int main() {
    printf("PID programu catcher: %d \n", getpid());

    struct sigaction action;
    action.sa_sigaction = handle_SIGUSR1;  
    action.sa_flags = SA_SIGINFO;
    sigemptyset(&action.sa_mask);
    sigaction(SIGUSR1, &action, NULL);

    while(1) {
    }
    return 0;
}