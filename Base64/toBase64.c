/*
Possible errors:
	- invalid file name
	- too many input arguments
	- cyrillic letters make program go brrrrr
*/

#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encryp (int * input, size_t letterAmount, char output[4]){
	output[0] = alphabet[input[0] >> 2];
	if(letterAmount == 1){
		output[1] = alphabet[(input[0] & 0x3) << 4];
		output[2] = '=';
		output[3] = '=';
	}
	else{
		output[1] = alphabet[((input[0] & 0x3) << 4) | (input[1] >> 4)];
		if(letterAmount == 2) {
			output[2] = alphabet[((input[1] & 0xF) << 2)];
			output[3] = '=';
		}
		else{
			output[2] = alphabet[((input[1] & 0xF) << 2) | (input[2] >> 6)];
			output[3] = alphabet[input[2] & 0x3F];
		}
	}
}

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];
	FILE * inputFile = fopen(inputFileName, "rb");
	
	int inpFileNMLen = strlen(inputFileName);
	char * fileSuffix = ".base64";
	int flSuffLen = strlen(fileSuffix) + 1;
	char * fileName	= calloc(inpFileNMLen + flSuffLen, sizeof(char));
	strncpy(fileName, inputFileName, inpFileNMLen);
	for (int i = 0; i < flSuffLen; i++) {
		fileName[inpFileNMLen + i] = fileSuffix[i];
	}

	FILE * outputFile = fopen(fileName, "w");
	
	int currentLetters[3];

	while(EOF != currentLetters[0]){
		int letterAmount = 0;
		currentLetters[0] = fgetc(inputFile);

		if (EOF != currentLetters[0]){
			letterAmount++;
			currentLetters[1] = fgetc(inputFile);
			
			if (EOF != currentLetters[1]){
				letterAmount++;
				currentLetters[2] = fgetc(inputFile);
				
				if (EOF != currentLetters[2]){
					letterAmount++;
				}
			}
			char output[4] = {0};
			encryp(currentLetters, letterAmount, output);
			//printf("%s", output); // --------------------> to print the result
			fprintf(outputFile, "%c%c%c%c", output[0], output[1], output[2], output[3]);
		}
	}	

	printf("\n");
	free(fileName);
	fclose(inputFile);
	fclose(outputFile);
}
