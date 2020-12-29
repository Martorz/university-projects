#ifndef SORTING_H
#define SORTING_H

int compareLTU (void * x, void * y);

int compareUTL (void * x, void * y);

void mysort (void * arr, size_t num, size_t size, int (*comparator)(void*, void*));

#endif