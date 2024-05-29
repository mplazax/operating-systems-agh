#include <stdio.h>
#ifdef DYNAMIC
#include <dlfcn.h>
#endif

#ifndef DYNAMIC
extern int test_collatz_convergence(int, int);
#endif

int main() {
    int numbers[] = {6, 19, 27, 15};
    int i;

#ifdef DYNAMIC
    void* handle = dlopen("libcollatz.so", RTLD_LAZY);
    if (!handle) {
        fprintf(stderr, "Cannot open library: %s\n", dlerror());
        return 1;
    }

    int (*test_collatz_convergence)(int, int);
    *(void**) (&test_collatz_convergence) = dlsym(handle, "test_collatz_convergence");
    if (!test_collatz_convergence) {
        fprintf(stderr, "Cannot load function: %s\n", dlerror());
        return 1;
    }
#endif

    for (i = 0; i < 4; i++) {
        printf("Number %d converges to 1 in %d iterations.\n",
               numbers[i], test_collatz_convergence(numbers[i], 1000));
    }

#ifdef DYNAMIC
    dlclose(handle);
#endif

    return 0;
}
