/*
 * Possible errors:
	- invalid file name
	- too many input arguments
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "mergesort.h"


int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];

	char * sortedListName = mergeSort(inputFileName);

	FILE * inputFile = fopen(sortedListName, "rb");
	struct list *numberList = NULL;
	int listLength = 0;
	int readResult = 1;

	while (readResult > 0) {
		int reader = 0;
		readResult = fscanf(inputFile, "%d", &reader);
		insertLast(&numberList, reader);
		listLength++;
	}

	if (readResult <= 0) {
		listLength--;
	}

	for (int i = 0; i < listLength; i++) {
		printf("%d \n", getByIndex(numberList, i));
	}
}