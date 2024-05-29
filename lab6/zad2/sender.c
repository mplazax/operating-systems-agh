#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

#define FIFO_NAME "potok"

int main() {
    double start, end, result;
    int fd;

    // Tworzenie potoku nazwanego, jeśli nie istnieje
    if (mkfifo(FIFO_NAME, 0666) == -1) {
        perror("mkfifo");
        exit(1);
    }

    printf("Podaj początek przedziału całkowania: ");
    scanf("%lf", &start);
    printf("Podaj koniec przedziału całkowania: ");
    scanf("%lf", &end);

    // Otwieranie potoku do zapisu i wysyłanie danych
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, &start, sizeof(double));
    write(fd, &end, sizeof(double));
    close(fd);

    // Otwieranie potoku do odczytu i odbieranie wyniku
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    read(fd, &result, sizeof(double));
    close(fd);

    printf("Wartość całki wynosi: %f\n", result);
    return 0;
}
