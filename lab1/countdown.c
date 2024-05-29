#include <stdio.h>

int main() {
    int j = 0;
    for (int i = 10; i >= 0; i--) {
        j++;
        printf("%d\n", i); 
        printf("         %d\n", j);
        if (j > 20) {
            return 1;
        }
        i=i+1;
    }
    return 0;
}
