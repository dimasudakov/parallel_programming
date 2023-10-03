/*
    author: Sudakov Dima 11-101
*/

#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <string>

using namespace std;


int main() {
    const int number = 210;
    int res = 0;

    omp_set_dynamic(0);

    int thread_count = 8;

    omp_set_num_threads(thread_count);
#pragma omp parallel for reduction(+:res)
    for (int i = 0; i < number; i++) {
        res += 2 * i + 1;
    }

    cout << "210 ^ 2 == " << res;
}