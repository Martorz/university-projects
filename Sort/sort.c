/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- invalid file name
	- too many input arguments
	- cyrillic letters make program go brrrrr
	- input character that are different from nums, space, EOF or .
 */

#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include "sorting.h"

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

	FILE * inputFile = fopen(inputFileName, "rb");
	char reader = 0;
	int i = 0;
	float numArray[100];
	do {
		float number = 0;
		reader = fgetc(inputFile);
		do {
			number = number * 10 + (reader - '0');
			reader = fgetc(inputFile);
		} while (reader >= '0' && reader <= '9');
		if (reader == '.'){
			reader = fgetc(inputFile);
			float floater = 0.1;
			while (reader >= '0' && reader <= '9') {
				number = number + (reader - '0') * floater;
				floater /= 10;
				reader = fgetc(inputFile);
			}
		}
		//printf("%f\n", number);
		numArray[i] = number;
		//printf("%f\n", numArray[i]);
		i++;
	} while (i < 100 && EOF != reader && '\n' != reader);
	//printf("%d\n", i);
	for (int j = 0; j < i; j++)
	{
		printf("%f\n", numArray[j]);
	}

	mysort(numArray, i);
	for (int j = 0; j < i; j++)
	{
		printf("%f\n", numArray[j]);
	}
}