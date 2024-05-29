#include "collatz.h"

int collatz_conjecture(int input) {
    return (input % 2 == 0) ? input / 2 : input * 3 + 1;
}

int test_collatz_convergence(int input, int max_iter) {
    int count = 0;
    while (input != 1 && count < max_iter) {
        input = collatz_conjecture(input);
        count++;
    }
    return (input == 1) ? count : -1;
}
