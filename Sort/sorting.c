#include <stdio.h>
#include <assert.h>
#include <string.h>

void swap (double * x, double * y){
	assert(x && y);
	double t = *x;
	*x = *y;
	*y = t;
}

void compareLTU (double * x, double * y){
	if (*x < *y) {
		swap(x, y);
	}
}

void compareUTL (double * x, double * y){
	if (*x > *y) {
		swap(x, y);
	}
}

void mysort (double * arr, size_t num, void (*comparator)(double*, double*)){
	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num; j++) {
			comparator(arr + i, arr + j);
		}
	}

}
