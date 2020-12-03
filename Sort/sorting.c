#include <stdio.h>
#include <assert.h>

void swap (double * x, double * y){
	assert(x && y);
	double t = *x;
	*x = *y;
	*y = t;
}

void mysort (double * arr, size_t num/*, size_t size, int (*comparator)(void*, void*)*/){
	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num; j++) {
			if (arr[i] > arr[j]) {
				swap(arr + i, arr + j);
			}
		}
	}
}
