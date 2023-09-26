#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

const int MIN_VALUE = -20;
const int MAX_VALUE = 30;

int main() {
    int tread_cnt;
    int n = 30;
    int max = MIN_VALUE - 1, min = MAX_VALUE + 1;
    int *a = new int[n];

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        a[i] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);

        if (a[i] % 9 == 0) cout << "!" << a[i];
        else cout << a[i] << " ";
    }

    cout << "\n\nEnter thread count: ";
    try {
        cin >> tread_cnt;
    }
    catch (const std::exception &) {
        tread_cnt = 3;
    }

    int count9 = 0;
#pragma omp parallel for num_threads(threadCount)
    for (int i = 0; i < n; i++) {
        if (a[i] % 9 == 0) {
#pragma omp atomic
            count9++;
        }

        if (i == 0) cout << "thread cnt: " << omp_get_num_threads() << endl;
    }

    cout << "count: " << count9;
}
