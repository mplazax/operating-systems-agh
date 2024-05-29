#include <stdio.h>
#include <time.h>

#ifdef BUFFER_ENABLED
#define BUFFER_SIZE 1024
void reverse_write(FILE* in_file, FILE* out_file){

    char buffer[BUFFER_SIZE];

    fseek(in_file, 0, SEEK_END);
    long bytes_left = ftell(in_file);

    
    while(bytes_left > 0){
        long bytes_to_read = bytes_left > BUFFER_SIZE ? BUFFER_SIZE : bytes_left;
        fseek(in_file, -bytes_to_read, SEEK_CUR);

        size_t bytes_read = fread(buffer, sizeof(char), bytes_to_read, in_file);


        char temp;
        for(int i = 0; i < bytes_read/2; i++){
            temp = buffer[i];
            buffer[i] = buffer[bytes_read - 1 - i];
            buffer[bytes_read - 1 - i] = temp;
        }

        fwrite(buffer, sizeof(char), bytes_read, out_file);
        fseek(in_file, -BUFFER_SIZE, SEEK_CUR);
        
        bytes_left -= bytes_read;
    }
}

#else
    void reverse_write(FILE* in_file, FILE* out_file) {
        fseek(in_file, -1, SEEK_END);
        long bytes_left = ftell(in_file) + 1;
        while (bytes_left-- > 0) {
            char c = fgetc(in_file);
            fputc(c, out_file);
            fseek(in_file, -2, SEEK_CUR);
        }

        return;
    }
#endif


int main(int argc, char* argv[]) {
    if (argc != 3) {
        perror("Niepoprawna liczba argumentów, oczekiwane 2");
        return 1;
    } 

    // argv[0] to nazwa programu

    FILE *in_file  = fopen(argv[1], "rb"); 

    if (in_file == NULL) {
        perror("Błąd w otwieraniu pliku 1");
        return 1;
    }

    FILE *out_file = fopen(argv[2], "wb"); 

    if (out_file == NULL) {
        perror("Błąd w otwieraniu pliku 2");
        return 1;
    }
    
    clock_t start, end;
    double working_time;

    start = clock();

    reverse_write(in_file, out_file);

    end = clock();
    working_time = ((double) (end - start)) / CLOCKS_PER_SEC;
    
    printf("Czas działania programu: %f sekund\n", working_time);

    if (fclose(in_file) == EOF) {
        perror("Błąd w zamykaniu pliku 1");
        return 1;
    }

    if (fclose(out_file) == EOF) {
        perror("Błąd w zamykaniu pliku 2");
        return 1;
    }

    return 0;
}



