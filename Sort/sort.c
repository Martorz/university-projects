/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- invalid file name
	- too many input arguments
	- input character that are different from nums, space, EOF or .
	- too many temp files
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
//#include "linkedlist.h"

#define MAX_ITEMS_IN_FILE 100

// ***START OF LINKED LIST***
// How to put in a separate file?

struct list {
	double x;
	struct list* next;
};

struct list *firstItems = NULL;
struct list *fileArrayID = NULL; //CRUTCH

void insertLast(double data) { //How to give the head of a list as a parameter?

	struct list *link = calloc(1, sizeof(struct list*));

	link->x = data;

   	if (firstItems != NULL){
		struct list* findLast = firstItems;
		while (findLast->next != NULL) {
	   		findLast = findLast->next;
		}
		findLast->next = link;
	}
	else {
		firstItems = link;
	}
}

void insertLastF(double data) { //CRUTCH

	struct list *link = calloc(1, sizeof(struct list*));

	link->x = data;

   	if (fileArrayID != NULL){
		struct list* findLast = fileArrayID;
		while (findLast->next != NULL) {
	   		findLast = findLast->next;
		}
		findLast->next = link;
	}
	else {
		fileArrayID = link;
	}
}

double getByIndex(struct list* h, size_t idx){
	int k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	return h->x;
}

void insertByIndex(struct list* h, size_t idx, double data){
	int k = 0;
	for (k = 0; k < idx; k++){
		h = h->next;
	}
	h->x = data;
}

void removeNode(struct list* h, size_t index){
	int k = 0;
	struct list *previous = NULL;
	if (index == 0) {
		firstItems = h->next;
	}
	else {
		for (k = 0; k < index; k++){
			previous = h;
			h = h->next;
		}
		previous->next = h->next;
	}
	free(h);
}

void removeNodeF(struct list* h, size_t index){ //CRUTCH
	int k = 0;
	struct list *previous = NULL;
	if (index == 0) {
		fileArrayID = h->next;
	}
	else {
		for (k = 0; k < index; k++){
			previous = h;
			h = h->next;
		}
		previous->next = h->next;
	}
	free(h);
}

size_t findMinItemID(struct list * arr) {
	size_t itemID = 0;
	size_t counter = 0;
	double itemValue = getByIndex(arr, itemID);
	while (arr != NULL) {
		if (arr->x < itemValue) {
			itemValue = arr->x;
			itemID = counter;
		}
		counter++;
		arr = arr->next;
	}
	return itemID;
}

size_t findMaxItemID(struct list * arr) {
	size_t itemID = 0;
	size_t counter = 0;
	double itemValue = getByIndex(arr, itemID);
	while (arr != NULL) {
		if (arr->x > itemValue) {
			itemValue = arr->x;
			itemID = counter;
		}
		counter++;
		arr = arr->next;
	}
	return itemID;
}

// ***END OF LINKED LIST***

size_t numLength (size_t number) {
	size_t counter = 0;
	while (number > 0) {
		number /= 10;
		counter++;
	}
	return counter;
}

char * numToStr (size_t number, size_t numLen) {
	char * stringNum = calloc(numLen + 1, sizeof(char));
	//stringNum[numLen] = '';
	for (int i = numLen - 1; i >= 0; i--) {
		stringNum[i] = (char)('0' + number % 10);
		number /= 10;
	}
	return stringNum;
}

char * createFileName(size_t fileCounter) {
	char * numberEnding = numToStr(fileCounter, numLength(fileCounter));
	char * outputFileName = calloc(strlen("temp_") + numLength(fileCounter) + 1, sizeof(char));
	strncpy(outputFileName, "temp_", strlen("temp_") + 1);
	strcat(outputFileName, numberEnding);
	free(numberEnding);
	//outputFileName[strlen("temp_") + numLength(fileCounter)] = '';
	return outputFileName;
}

void fillWithZero(double * array, size_t length){
	for (int i = 0; i < length; i++) {
		array[i] = 0;
	}
}

void readTempFiles(size_t length, FILE ** inputFiles, struct list * firstItems) {
	for (int i = 0; i < length; i++) {
		char * tempFileName = createFileName(i + 1);
		inputFiles[i] = fopen(tempFileName, "r");
		free(tempFileName);
	}

	for (int i = 0; i < length; i++) {
		insertLastF(i);
	}

	double reader = 0;
	for (int i = 0; i < length; i++) {
		if (NULL != inputFiles[i]) {
			fscanf(inputFiles[i], "%lf", &reader);
			insertLast(reader);
		}
	}
}



int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];

	char * flag;
	if (argv[2] == NULL){
		printf("Error: Flag is missing. Default flag is set: -ltu.\n");
		flag = "-ltu";
	}
	else if (strcmp(argv[2], "-ltu") != 0 && strcmp(argv[2], "-utl") != 0) {
		printf("Error: Invalid flag. Default flag is set: -ltu.\n");
		flag = "-ltu";
	}
	else {
		flag = argv[2];
	}

	int fileCounter = 0;
	int entriesCounter = 0;
	int readResult = 1;
	FILE * inputFile = fopen(inputFileName, "r");
	while (readResult > 0) {
		
		size_t length = 0;
		double numArray[MAX_ITEMS_IN_FILE]; //is it okay to use a const 
		do {
			readResult = fscanf(inputFile, "%lf", &numArray[length]);
			length++;
			entriesCounter++;
		} while (length < MAX_ITEMS_IN_FILE && readResult > 0);

		if (readResult <= 0) {
			length--;
			entriesCounter--;
		}

		if (strcmp(flag, "-ltu") == 0) {
			mysort(numArray, length, &compareLTU);	
		}
		else {
			mysort(numArray, length, &compareUTL);
		}

		if (length != 0) {
			fileCounter++;
			FILE * outputFile = fopen(createFileName(fileCounter), "w"); //how to deallocate?
			for (int i = 0; i < length; i++){
				fprintf(outputFile, "%lf ", numArray[i]);
			}
			fclose(outputFile);
		}

		fillWithZero(numArray, MAX_ITEMS_IN_FILE);
	}

	fclose(inputFile);

	// *** SORTING TEMP FILES ***

	FILE ** inputFiles = (FILE**)calloc(fileCounter, sizeof(FILE*));
	
	FILE * outputFile = fopen("output.txt", "w");

	readTempFiles(fileCounter, inputFiles, firstItems);
	
	int itemID;
	size_t (*finder) (struct list *);
	if (strcmp(flag, "-ltu") == 0) {
			finder = findMinItemID;
		}
	else {
		finder = findMaxItemID;
	}

	for (int i = 0; i < entriesCounter; i++){
		itemID = finder(firstItems);
		fprintf(outputFile, "%lf ", getByIndex(firstItems, itemID));
		double reader = 0;
		if (fscanf(inputFiles[(int)(getByIndex(fileArrayID, itemID))], "%lf", &reader) <= 0) {
			removeNode(firstItems, itemID);
			removeNodeF(fileArrayID, itemID);
		}
		else {
			insertByIndex(firstItems, itemID, reader);
		}
	}

	// *** DELETING TEMP FILES ***

	for (int i = 0; i < fileCounter; i++) {
		fclose(inputFiles[i]);
	}
	free(inputFiles);

	for (int i = 1; i <= fileCounter; i++) {
		remove(createFileName(i));
	}

	fclose(outputFile);
}