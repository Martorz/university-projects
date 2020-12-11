#ifndef SORTING_H
#define SORTING_H

void mysort (int* arr, size_t num, void (*comparator)(int*, int*));  //приделать void*

void compareLTU (int * x, int * y);

void compareUTL (int * x, int * y);

#endif
