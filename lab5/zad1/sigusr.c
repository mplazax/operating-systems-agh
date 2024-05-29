#include <stdio.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>


void USR1_handler(int signal_number){
    printf("Otrzymano sygnał SIGUSR o numerze: %d\n", signal_number);
}


int main(int argc, char* argv[]) {
    if (argc != 2) {
        perror("Uzycie: ./sigusr [none|ignore|handler|mask]");
        return 1;
    }

    if (!strcmp(argv[1], "none")) {
        //nothing happens
    } 
    else if (!strcmp(argv[1], "ignore")) {
        signal(SIGUSR1, SIG_IGN);
    } 
    else if (!strcmp(argv[1], "handler")) {
        signal(SIGUSR1, USR1_handler);
    } 
    else if (!strcmp(argv[1], "mask")) {
        sigset_t set;
        sigemptyset(&set);        
        sigaddset(&set, SIGUSR1);  
        if (sigprocmask(SIG_BLOCK, &set, NULL) == -1) {
            perror("sigprocmask");
        } else {
            printf("SIGUSR1 jest teraz maskowany.\n");
        }
    } 
    else {
        // default case
        perror("Uzycie: ./sigusr [none|ignore|handler|mask]");
        return 1;
    }

    raise(SIGUSR1);

    return 0;
};