/*
 * Flag names:
	-ltu - lower to upper
	-utl - upper to lower

 * Possible errors:
	- invalid file name
	- too many input arguments
	- cyrillic letters make program go brrrrr
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

	//FILE * inputFile = fopen(inputFileName, "rb");
}