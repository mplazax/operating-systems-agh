#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

#define FIFO_NAME "potok"

double f(double x) {
    return 4.0 / (x * x + 1);
}

double compute_integral(double start, double end, double width) {
    double sum = 0.0;
    for (double x = start; x < end; x += width) {
        sum += f(x) * width;
    }
    return sum;
}

int main() {
    double start, end, result;
    int fd;

    // Otwieranie potoku do odczytu
    fd = open(FIFO_NAME, O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    read(fd, &start, sizeof(double));
    read(fd, &end, sizeof(double));
    close(fd);

    // Obliczanie całki
    result = compute_integral(start, end, 0.001);  // Zakładamy stałą szerokość prostokąta

    // Otwieranie potoku do zapisu i wysyłanie wyniku
    fd = open(FIFO_NAME, O_WRONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }
    write(fd, &result, sizeof(double));
    close(fd);

    return 0;
}
