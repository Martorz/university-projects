/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- invalid file name
	- too many input arguments
	- input character that are different from nums, space, EOF or .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "sorting.h"

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

void fillWithZero(double * array, size_t length){
	for (int i = 0; i < length; i++) {
		array[i] = 0;
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
	int readResult = 1;
	FILE * inputFile = fopen(inputFileName, "rb");
	size_t length = 0;
	while (readResult > 0) {
		fileCounter++;
		//size_t length = 0;
		length = 0;
		double numArray[MAX_ITEMS_IN_FILE]; //is it okay to use a const 
		do {
			readResult = fscanf(inputFile, "%lf", &numArray[length]);
			length++;
		} while (length < MAX_ITEMS_IN_FILE && readResult > 0);

		if (readResult <= 0) {
			length--;
		}

		if (strcmp(flag, "-ltu") == 0) {
			mysort(numArray, length, &compareLTU);	
		}
		else {
			mysort(numArray, length, &compareUTL);
		}

		if (length != 0) {
			FILE * outputFile = fopen(createFileName(fileCounter), "w"); //how to deallocate?
			for (int i = 0; i < length; i++){
				fprintf(outputFile, "%lf ", numArray[i]);
			}
			fclose(outputFile);
		}

		fillWithZero(numArray, MAX_ITEMS_IN_FILE);
		//printf("Length: %ld, read result: %d\n", length, readResult);
	}
	//printf("Last length: %ld, last read result: %d\n", length, readResult);

	fclose(inputFile);
}