#ifndef SORTING_H
#define SORTING_H

void compareLTU (void * x, void * y);

void compareUTL (void * x, void * y);

void mysort (void * arr, size_t num, size_t size, void (*comparator)(void*, void*));

#endif