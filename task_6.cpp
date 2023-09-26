#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main() {
    const int N = 10;
    int a[N], b[N];

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 99);

    for (int i = 0; i < N; ++i) {
        a[i] = dis(gen);
        b[i] = dis(gen);
    }

    cout << "Array a: " << '\n';
    for (int i = 0; i < N; i++) {
        cout << a[i] << ' ';
        if(i == N - 1) cout << '\n';
    }
    cout << "Array b: " << '\n';
    for (int i = 0; i < N; i++) {
        cout << b[i] << ' ';
        if(i == N - 1) cout << '\n';
    }

    double sum_a = 0.0, sum_b = 0.0;

    #pragma omp parallel for reduction(+:sum_a, sum_b)
    for (int i = 0; i < N; ++i) {
        sum_a += a[i];
        sum_b += b[i];
    }

    double avg_a = sum_a / N;
    double avg_b = sum_b / N;

    cout << "Arithmetic mean of array a: " << avg_a << endl;
    cout << "Arithmetic mean of array b: " << avg_b << endl;

    return 0;
}