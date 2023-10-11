#include <omp.h>
#include <stdio.h>
#include <iostream>


int main() {
    int a = 0, b = 0;

    omp_set_dynamic(0);

    omp_set_num_threads(2);

    printf("First region: A before %d, B before %d\n\n",  a, b);

#pragma omp parallel private(a) firstprivate(b)
    {
#pragma omp critical
        {
            a += omp_get_thread_num();
            b += omp_get_thread_num();
            printf("	A = %d, thread count %d\n", a, omp_get_thread_num());
            printf("	B = %d, thread count %d\n", b, omp_get_thread_num());
        }
    }
    printf("\nFirst region: A after %d, B after %d\n", a, b);

    std::cout << "\n";

    omp_set_num_threads(4);

    printf("Second region: A before %d, B before %d\n\n", a, b);
#pragma omp parallel shared(a) private(b)
    {
#pragma omp critical
        {
            a -= omp_get_thread_num();
            b -= omp_get_thread_num();
            printf("	A = %d, thread count %d\n", a, omp_get_thread_num());
            printf("	B = %d, thread count %d\n", b, omp_get_thread_num());
        }
    }
    printf("\nSecond region: A after %d, B after %d\n", a, b);

    return 0;
}