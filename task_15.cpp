/*
    author: Sudakov Dima 11-101
*/

#include <iostream>
#include <vector>
#include <omp.h>

using namespace std;


int main() {
    int left, right = 0;
    vector<int> result;

    cout << "Введите левую границу:";
    cin >> left;

    cout << "Введите правую границу";
    cin >> right;

    if (right < left) {
        cerr << "Некорректный ввод";
        return 0;
    }

    int thread_count = 8;

    omp_set_dynamic(0);
    omp_set_num_threads(thread_count);


    vector<bool> prime(right + 1, true);

    for (int i = 2; i <= right; ++i) {
        if (prime[i]) {
            if (i >= left) {
                result.push_back(i);
            }
#pragma omp parallel for
            for (int j = 2 * i; j <= right; j += i) {
                prime[j] = false;
            }
        }
    }

    cout << "Кол-во простых чисел на отрезке от: " << left << " до: " << right << endl;

    cout << "Простые числа: ";
    for (auto u: result) {
        cout << u << ' ';
    }
}
