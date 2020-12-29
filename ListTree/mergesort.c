/*
	* returns the name of sorted file
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
	const char * tempName = "temp_";
	char * numberEnding = numToStr(fileCounter, numLength(fileCounter));
	char * outputFileName = calloc(strlen(tempName) + numLength(fileCounter) + 1, sizeof(char));
	strncpy(outputFileName, tempName, strlen(tempName) + 1);
	strcat(outputFileName, numberEnding);
	free(numberEnding);
	//outputFileName[strlen("temp_") + numLength(fileCounter)] = '';
	return outputFileName;
}

void fillWithZero(int * array, size_t length){
	for (int i = 0; i < (int)length; i++) {
		array[i] = 0;
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

void readTempFiles(size_t length, FILE ** inputFiles, struct list ** firstItems) {
	for (int i = 0; i < (int)length; i++) {
		char * tempFileName = createFileName(i + 1);
		// ----------------------------------------------------------------------------------> GARBAGE
		if (fileExist(tempFileName) == 0) {
			printf("Error: Invalid file name. File name: %s\n", tempFileName);
			i--;
		}
		else{
			inputFiles[i] = fopen(tempFileName, "r");
		}
		free(tempFileName);
	}

	int reader = 0;
	for (int i = 0; i < (int)length; i++) {
		if (NULL != inputFiles[i]) {
			fscanf(inputFiles[i], "%d", &reader);
			insertLast(firstItems, reader);
		}
	}
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
		fprintf(outputFile, "%d ", getByIndex(firstItems, itemID));
		int reader = 0;
		if (fscanf(inputFiles[(int)(getByIndex(fileArrayID, itemID))], "%d", &reader) <= 0) {
			removeNode(&firstItems, itemID);
			removeNode(&fileArrayID, itemID);
		}
		else {
			insertByIndex(firstItems, itemID, reader);
		}
	}

	clearList(firstItems);
	clearList(fileArrayID);
}

char * mergeSort(char * inputFileName) {
	if (inputFileName == NULL){
		printf("Error: File reading error. File name is missing.\n");
		return "";
	}

	if (fileExist(inputFileName) == 0) {
		printf("Error: Invalid file name. File name: %s\n", inputFileName);
		return "";
	}

	char * flag = "-ltu";

	int fileCounter = 0;
	int entriesCounter = 0;
	int readResult = 1;
	FILE * inputFile = fopen(inputFileName, "r");
	while (readResult > 0) {
		
		size_t length = 0;
		int numArray[MAX_ITEMS_IN_FILE];
		do {
			readResult = fscanf(inputFile, "%d", &numArray[length]);
			length++;
			entriesCounter++;
		} while (length < MAX_ITEMS_IN_FILE && readResult > 0);

		if (readResult <= 0) {
			length--;
			entriesCounter--;
		}

		if (strcmp(flag, "-ltu") == 0) {
			mysort(numArray, length, sizeof(int), compareLTU);	
		}
		else {
			mysort(numArray, length, sizeof(int), compareUTL);
		}

		if (length != 0) {
			fileCounter++;
			char * tempFileName = createFileName(fileCounter);
			FILE * outputFile = fopen(tempFileName, "w");
			free(tempFileName);
			for (int i = 0; i < (int)length; i++){
				fprintf(outputFile, "%d ", numArray[i]);
			}
			fclose(outputFile);
		}

		fillWithZero(numArray, MAX_ITEMS_IN_FILE);
	}

	fclose(inputFile);

	// *** SORTING TEMP FILES *** 

	FILE ** inputFiles = (FILE**)calloc(fileCounter, sizeof(FILE*));
	FILE * outputFile = fopen("sortedList.txt", "w");

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

	return "sortedList.txt";
}
