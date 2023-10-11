#include <omp.h>
#include <stdio.h>

int a = 3, b = 1;
int main() {
    omp_set_dynamic(0);
    omp_set_num_threads(a);

#pragma omp parallel if(omp_get_max_threads() > 1)
    printf("First region: current thread %d, all threads %d\n", omp_get_thread_num(), omp_get_num_threads());

    omp_set_num_threads(b);

#pragma omp parallel if(omp_get_max_threads() > 1)
    printf("Second region: current thread %d, all threads %d\n", omp_get_thread_num(), omp_get_num_threads());

    return 0;
}