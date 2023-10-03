/*
    author: Sudakov Dima 11-101
*/

#include <iostream>
#include <omp.h>
#include <math.h>
#include <stdio.h>
#include <string>

using namespace std;

const int BITS_CNT = 30;

int main() {
    int8_t a[BITS_CNT] = {1, 0, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1};
    double res = 0;

    omp_set_dynamic(0);

    int thread_count = 8;

    omp_set_num_threads(thread_count);
#pragma omp parallel for reduction(+:res)
    for (int i = 0; i < BITS_CNT; i++) {
        if (a[i] == 1) {
            res = res + a[i] * pow(2, BITS_CNT - i - 1);
        }
    }

    cout << "Число в десятичной системе счисления: " << res;
}