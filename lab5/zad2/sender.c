
#include <signal.h>
#include <sys/types.h>

#include <stdlib.h>
#include <stdio.h>

#include <string.h>
#include <stdlib.h>
#include <unistd.h>


void handle_SIGUSR1(int sig) {
    printf("Otrzymano potwierdzenie od catcher\n");
    exit(0);
}

int main(int argc, char** argv) {
    if (argc != 3) {
        perror("Uycie: ./sender <catcher pid> <tryb pracy>");
        return 1;
    }

    int catcher_pid = atoi(argv[1]);
    int mode = atoi(argv[2]);

    signal(SIGUSR1, handle_SIGUSR1);

    union sigval value = {mode};

    sigqueue(catcher_pid, SIGUSR1, value);

    printf("Wyslano sygnal z nowym trybem pracy %d\n", mode);

    pause();
    return 0;
}
