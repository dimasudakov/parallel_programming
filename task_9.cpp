#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

const int MIN_VALUE = -20;
const int MAX_VALUE = 30;

void init_matrix(int **a, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
            cout << a[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int thread_cnt;
    int n = 6, m = 8;
    int max = MIN_VALUE - 1, min = MAX_VALUE + 1;
    int **d = new int *[n];

    for (int i = 0; i < n; i++)
        d[i] = new int[m];

    srand(time(NULL));
    init_matrix(d, n, m);

    cout << "Enter thread count: ";
    try {
        cin >> thread_cnt;
    }
    catch (const std::exception &) {
        thread_cnt = 3;
    }


#pragma omp parallel for num_threads(threadCount)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (d[i][j] > max)
#pragma omp critical
            {
                max = d[i][j];
            }

            if (d[i][j] < min)
#pragma omp critical
            {
                min = d[i][j];
            }

        }

        if (i == 0) cout << "thread cnt: " << omp_get_num_threads();
    }

    cout << "minimum: " << min << ", " << "maximum: " << max;
}
