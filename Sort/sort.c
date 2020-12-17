/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- too many temp files
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"
#include "linkedlist.h"

#define MAX_ITEMS_IN_FILE 100

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

void fillWithZero(double * array, size_t length){ //change for memset
	for (int i = 0; i < length; i++) {
		array[i] = 0;
	}
}

void readTempFiles(size_t length, FILE ** inputFiles, struct list ** firstItems) {
	for (int i = 0; i < length; i++) {
		char * tempFileName = createFileName(i + 1);
		inputFiles[i] = fopen(tempFileName, "r");
		free(tempFileName);
	}

	double reader = 0;
	for (int i = 0; i < length; i++) {
		if (NULL != inputFiles[i]) {
			fscanf(inputFiles[i], "%lf", &reader);
			insertLast(firstItems, reader);
		}
	}
}

int fileExist(char * fileName) {
	FILE * input;
    if (input = fopen(fileName, "r")){
        fclose(input);
        return 1;
    }
    return 0;
}

void sortTempFiles(FILE ** inputFiles, FILE * outputFile, int fileCounter, int entriesCounter, char * flag) {
	
	struct list *firstItems = NULL;
	
	readTempFiles(fileCounter, inputFiles, &firstItems);

	struct list *fileArrayID = NULL;
	for (int i = 0; i < fileCounter; i++) {
		insertLast(&fileArrayID, i);
	}
	
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
			removeNode(&firstItems, firstItems, itemID);
			removeNode(&fileArrayID, fileArrayID, itemID);
		}
		else {
			insertByIndex(firstItems, itemID, reader);
		}
	}
}

int main(int argc, char** argv){
	if (argv[1] == NULL){ //лучше проверять argc
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}

	if (fileExist(argv[1]) == 0) {
		printf("Error: Invalid file name. File name: %s\n", argv[1]);
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

	if (argv[3] != NULL) {
		printf("Error: Too many arguments. All the excess arguments will be ignored.\n");
	}

	int fileCounter = 0;
	int entriesCounter = 0;
	int readResult = 1;
	FILE * inputFile = fopen(inputFileName, "r");
	while (readResult > 0) {
		
		size_t length = 0;
		double numArray[MAX_ITEMS_IN_FILE];
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
			mysort(numArray, length, sizeof(double), compareLTU);	
		}
		else {
			mysort(numArray, length, sizeof(double), compareUTL);
		}

		if (length != 0) {
			fileCounter++;
			char * tempFileName = createFileName(fileCounter);
			FILE * outputFile = fopen(tempFileName, "w");
			free(tempFileName);
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

	sortTempFiles(inputFiles, outputFile, fileCounter, entriesCounter, flag);

	// *** DELETING TEMP FILES ***

	for (int i = 0; i < fileCounter; i++) {
		fclose(inputFiles[i]);
	}
	free(inputFiles);

	for (int i = 1; i <= fileCounter; i++) {
		char * tempFileName = createFileName(i);
		remove(tempFileName);
		free(tempFileName);
	}

	fclose(outputFile);
}
