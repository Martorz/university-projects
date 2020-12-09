/*
 * Possible errors:
	- invalid file name
	- too many input arguments
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

struct list {
	int x;
	struct list* next;
};

struct list *numberList = NULL;

void insertLast(int data) {

	struct list *link = calloc(1, sizeof(struct list*));

	link->x = data;

   	if (numberList != NULL){
		struct list* findLast = numberList;
		while (findLast->next != NULL) {
			findLast = findLast->next;
		}
		findLast->next = link;
	}
	else {
		numberList = link;
	}
}

int getByIndex(struct list* h, size_t idx){
	int k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	return h->x;
}

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];
	FILE * inputFile = fopen(inputFileName, "rb");
	int listLength = 0;
	int readResult = 1;

	while (readResult > 0) {
		int reader = 0;
		readResult = fscanf(inputFile, "%d", &reader);
		insertLast(reader);
		listLength++;
	}

	if (readResult <= 0) {
		listLength--;
	}

	for (int i = 0; i < listLength; i++) {
		printf("%d \n", getByIndex(numberList, i));
	}
}