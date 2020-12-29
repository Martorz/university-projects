/*
 * Possible errors:

 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "mergesort.h"
#include "tree.h"


int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name is missing.\n");
		return -1;
	}

	if (fileExist(argv[1]) == 0) {
		printf("Error: Invalid file name. File name: %s\n", argv[1]);
		return -1;
	}

	if (argc != 2) {
		printf("Error: Too many arguments. All the excess arguments will be ignored.\n");
	}

	char * inputFileName = argv[1];

	char * sortedListName = mergeSort(inputFileName);

	FILE * inputFile = fopen(sortedListName, "r");
	struct list *numberList = NULL;
	int listLength = 0;
	int readResult = 1;
	
	while (readResult == 1) {
		int reader = 0;
		readResult = fscanf(inputFile, "%d", &reader);
		insertLast(&numberList, reader);
		listLength++;
	}

	if (readResult <= 0) {
		listLength--;
		removeNode(&numberList, listLength);
	}
	node * root = NULL;
	root = linkedListIntoAVL(numberList, listLength);

	printPrefix(root, 0);

	clearTree(root);
	clearList(numberList);
	fclose(inputFile);
	remove(sortedListName);

}