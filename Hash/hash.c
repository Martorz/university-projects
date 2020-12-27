/*
 * Possible errors:
 */

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashTable.h"

int fileExist(char * fileName) {
	FILE * input;
    if (input = fopen(fileName, "r")){
        fclose(input);
        return 1;
    }
    return 0;
}

char* readName(FILE * inputFile){
	char * name = calloc(255, sizeof(char));
	char temp = 0;
	int count = 0;
	temp = fgetc(inputFile);
	while(count < 254 && temp != ' '){
		name[count] = temp;
		count++;
		temp = fgetc(inputFile);
	}
	name[count] = '\0';
	return name;
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
	FILE * inputFile = fopen(inputFileName, "r");

	struct person * hashTable[TABLE_SIZE];
	initHashTable(hashTable);
	int height = 0, weight = 0;
	int readResult = 1;

	while (readResult > 0) {
		char * name = readName(inputFile);
		readResult = fscanf(inputFile, "%d %d", &height, &weight);
		if (readResult > 0) {
			hashTableInsert(hashTable, name, height, weight);
			fgetc(inputFile);
		}
	}
	printTable(hashTable);
	printf("\n");

	printf("Enter a name to look for it in the database. Enter \"quit\" to stop the program.\n");
	char command[255];
	scanf("%s", command);
	while(strcmp(command, "quit") != 0){
		struct person * who = hashTableFind(hashTable, command);
		if (who != NULL) {
			printf("Name: %s, height: %d, weight: %d.\n\n", who->name, who->data.height, who->data.weight);
		}
		else {
			printf("NOT FOUND.\n\n");
		}
		scanf("%s", command);
	}

	hashTableClear(hashTable);
	fclose(inputFile);
}