#include <stdio.h>

void mysort (void * head, size_t num, size_t size, int (*comparator)(void*, void*)){
	printf("%ld %ld\n", num, size);
}