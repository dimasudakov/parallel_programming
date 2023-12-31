#include <omp.h>
#include <stdio.h>
#include <iostream>

int main() {
    int a[10] = { -1, 3, -6, -12, 4, 5, 6, 8, 3, 11 } ;
    int b[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

    int max = - 20, min = 20;

    omp_set_num_threads(2);

#pragma omp parallel sections
    {
#pragma omp section
        {
            printf("thread id = %d, \n", omp_get_thread_num());
            for (int i = 0; i < 10; ++i)
            {
                if (a[i] < min)
                {
                    min = a[i];
                }
            }

            printf("min in array A: %d\n", min);
        }

#pragma omp section
        {
            printf("\nthread id = %d, \n", omp_get_thread_num());
            for (int i = 0; i < 10; ++i)
            {
                if (b[i] > max)
                {
                    max = b[i];
                }
            }

            printf("max in array B: %d", max);
        }
    }

    std::cout << "\n";
    return 0;
}