#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void swap (void * x, void * y, size_t size){
	assert(x && y);
	void * t = malloc(size);
	memcpy(t, x, size);
	memcpy(x, y, size);
	memcpy(y, t, size);

	free(t);
}

void compareLTU (void * x, void * y){
	double * a = x;
	double * b = y;
	if (*a < *b) {
		swap(x, y, sizeof(double));
	}
}

void compareUTL (void * x, void * y){
	double * a = x;
	double * b = y;
	if (*a > *b) {
		swap(x, y, sizeof(double));
	}
}

void mysort (void * arr, size_t num, size_t size, void (*comparator)(void*, void*)){
	assert(NULL != arr);

	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num; j++) {
			comparator(arr + i * size, arr + j * size);
		}
	}
}
