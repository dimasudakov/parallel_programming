#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <chrono>

using namespace std;

const int MIN_VALUE = 0;
const int MAX_VALUE = 20;

void init_matrix(int **a, int n, int m) {
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            a[i][j] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
        }
    }
}

void init_vector(int *a, int m) {
    for (int j = 0; j < m; ++j) {
        a[j] = MIN_VALUE + rand() % (MAX_VALUE - MIN_VALUE + 1);
    }
}

void multiply_matrix(int **a, int *b, int *c, int n, int m) {
    int count;

    for (int i = 0; i < n; ++i) {
        count = 0;
        for (int j = 0; j < m; ++j) {
            count += a[i][j] * b[j];
        }
        c[i] = count;
    }
}

void print_result(int *c, int n) {
    for (int j = 0; j < n; ++j) {
        cout << c[j] << " ";
    }
    cout << endl;
}

int main() {
    int n, m;
    double time_a, time_b;

    cin >> n;
    cin >> m;
    cout << endl;

    int **a = new int *[n];
    for (int i = 0; i < n; i++)
        a[i] = new int[m];

    int *b = new int[m];
    int *c = new int[m];

    srand(time(NULL));

    init_matrix(a, n, m);
    init_vector(b, m);

    auto begin = chrono::high_resolution_clock::now();
    multiply_matrix(a, b, c, n, m);
    auto end = chrono::high_resolution_clock::now();
    cout << "time a (NO PARALLEL): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns"
         << endl;

    begin = chrono::high_resolution_clock::now();
#pragma omp parallel
    {
        int count;
#pragma omp for schedule(static)
        for (int i = 0; i < n; ++i) {
            count = 0;
            for (int j = 0; j < m; ++j) {
                count += a[i][j] * b[j];
            }
            c[i] = count;
        }
    }

    end = chrono::high_resolution_clock::now();
    cout << "time b (PARALLEL): " << chrono::duration_cast<chrono::nanoseconds>(end - begin).count() << " ns" << endl;
}
