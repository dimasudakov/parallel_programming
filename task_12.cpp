/*
    author: Sudakov Dima 11-101
*/


#include <omp.h>
#include <stdio.h>

using namespace std;

const int N = 8;

int main() {
#pragma omp parallel num_threads(N)
    {
        for (int i = omp_get_num_threads(); i > 0; i--) {
#pragma omp barrier
            {
                if (i == omp_get_thread_num()) {
#pragma omp critical
                    cout << "\"Hello World\" printed from thread: " << omp_get_thread_num() << endl;
                }
            }
        }
    }
}
