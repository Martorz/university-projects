#include <stdio.h>
#include <assert.h>
#include <string.h>

void swap (int * x, int * y){
	assert(x && y);
	int t = *x;
	*x = *y;
	*y = t;
}

void compareLTU (int * x, int * y){
	if (*x < *y) {
		swap(x, y);
	}
}

void compareUTL (int * x, int * y){
	if (*x > *y) {
		swap(x, y);
	}
}

void mysort (int * arr, size_t num, void (*comparator)(int*, int*)){
	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num; j++) {
			comparator(arr + i, arr + j);
		}
	}

}
