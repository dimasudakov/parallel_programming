#include <omp.h>
#include <stdio.h>

int num = 8;

int main() {
#pragma omp parallel num_threads(num)
    printf("\"Hello World\" printed from thread %i\n", omp_get_thread_num());

    return 0;
}