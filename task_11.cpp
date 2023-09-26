#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

const int MIN_VALUE = -20;
const int MAX_VALUE = 30;
int check_max = MIN_VALUE - 1;

int main() {
    int thread_cnt;
    int n = 30;
    int mx7 = MIN_VALUE - 1;
    int *a = new int[n];

    srand(time(NULL));

    for (int i = 0; i < n; ++i) {
        a[i] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);

        if (a[i] % 7 == 0) cout << "!" << a[i] << ' ';
        else cout << a[i] << " ";

        if (a[i] % 7 == 0 && check_max < a[i]) {
            {
                check_max = a[i];
            }
        }
    }

    cout << "\n\nEnter thread count: ";
    try {
        cin >> thread_cnt;
    }
    catch (const std::exception &) {
        thread_cnt = 3;
    }

#pragma omp parallel for shared(max)
    for (int i = 0; i < n; i++) {
        if (a[i] % 7 == 0 && mx7 < a[i]) {
#pragma omp critical
            {
                mx7 = a[i];
            }
        }
        if (i == 0) cout << "\nthread count: " << omp_get_num_threads() << endl;
    }

    cout << endl << "max % 7: " << mx7 << endl;

    if (mx7 == (MIN_VALUE - 1)) {
        cout << "\ndon't find number % 7 = 0";
    } else {
        if (check_max == mx7) {
            cout << endl << "correct" << endl;
        }
    }
}
