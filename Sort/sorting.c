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

int compareLTU (void * x, void * y){
	double * a = x;
	double * b = y;
	if (*a < *b) {
		return 1;
	}
	else {
		return 0;
	}
}

int compareUTL (void * x, void * y){
	double * a = x;
	double * b = y;
	if (*a > *b) {
		return 1;
	}
	else {
		return 0;
	}
}

void mysort (void * arr, size_t num, size_t size, int (*comparator)(void*, void*)){
	assert(NULL != arr);

	char * array = (char *)arr; 

	for (size_t i = 0; i < num; i++) {
		for (size_t j = 0; j < num; j++) {
			if (comparator(array + i * size, array + j * size) == 1) {
				swap(array + i * size, array + j * size, size);
			} 
			
		}
	}
}
