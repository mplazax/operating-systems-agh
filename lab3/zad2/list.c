#include <stdio.h>
#include <dirent.h>
#include <stdlib.h>
#include <sys/stat.h>

int main() {
    DIR *working_directory = opendir(".");
    struct dirent *dir;
    struct stat buffer;
    long long total_size = 0;


    if (working_directory == NULL) {
        perror("Błąd otwierania katalogu");
        return 1;
    }

    while ((dir = readdir(working_directory)) != NULL) {
  
        if (stat(dir->d_name, &buffer) == 0) {
            if (!S_ISDIR(buffer.st_mode)) {
                printf("Plik %s Zajmuje %lld\n", dir->d_name, (long long)buffer.st_size);
                total_size += buffer.st_size;
            }
        } else {
            perror("Błąd funkcji stat");
            closedir(working_directory);
            return 1;
        }
    }

    closedir(working_directory);

    printf(": %lld\n", total_size);
    return 0;
}
