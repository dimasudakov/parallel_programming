#include <omp.h>
#include <stdio.h>
#include <iostream>


int t_cnt_a = 3, t_cnt_b = 4;
int const N = 12;

int main() {
	int a[N], b[N], c[N];

	int ax = 2, bx = 4, cx = 3;

	omp_set_dynamic(0);

	omp_set_num_threads(t_cnt_a);
#pragma omp parallel 
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++) {
			a[i] = i * ax;
			b[i] = i * bx;

			printf("Area 1: working thread number %d of %d threads, a[%d] = % d, b[%d] = % d\n", omp_get_thread_num(), omp_get_num_threads(), i, a[i], i, b[i]);
		}
	}

	std::cout << "\n";

	omp_set_num_threads(t_cnt_b);
#pragma omp parallel 
	{
#pragma omp for schedule(static)
		for (int i = 0; i < N; i++) {
			c[i] = (a[i] + b[i]) * cx;

			printf("Area 2: working thread number %d of %d threads, c[%d] = % d\n", omp_get_thread_num(), omp_get_num_threads(), i, c[i]);
		}
	}
}