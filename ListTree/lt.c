/*
 * Possible errors:

 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"
#include "mergesort.h"
#include "tree.h"

int fileExist(char * fileName) {
	FILE * input;
    if (input = fopen(fileName, "r")){
        fclose(input);
        return 1;
    }
    return 0;
}

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}

	if (fileExist(argv[1]) == 0) {
		printf("Error: Invalid file name. File name: %s\n", argv[1]);
		return -1;
	}

	if (argv[2] != NULL) {
		printf("Error: Too many arguments. All the excess arguments will be ignored.");
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
		removeNode(&numberList, numberList, listLength);
	}

	node * root = NULL;
	root = linkedListIntoAVL(numberList, listLength);

	printPrefix(root, 0);

	clearTree(root);
	clearList(numberList);
	fclose(inputFile);
	remove(sortedListName);

}