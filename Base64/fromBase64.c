/*
Possible errors:
	- '=' in the middle of a string;
	- wrong amount/lack of '=' in the end of a string.
	- invalid file name
	- too many input arguments
*/

#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void decryp (int * input, char output[3]){
	int origLetter[4];
	origLetter[0] = strchr(alphabet, (char)input[0]) - alphabet;
	origLetter[1] = strchr(alphabet, (char)input[1]) - alphabet;
	output[0] = (char)((origLetter[0] << 2) | (origLetter[1] >> 4));
	if(input[2] != '=') {
		origLetter[2] = strchr(alphabet, (char)input[2]) - alphabet;
		output[1] = (char)(((origLetter[1] << 4) & 0xFF) | (origLetter[2] >> 2));
		if(input[3] != '=') {
			origLetter[3] = strchr(alphabet, (char)input[3]) - alphabet;
			output[2] = (char)(((origLetter[2] << 6) & 0xFF) | origLetter[3]);
		}
	}
}

int base64Check(int letter){
	if ((letter >= 'A' && letter <= 'Z') || (letter >= 'a' && letter <= 'z') ||
		(letter >= '0' && letter <= '9')  || (letter == '+') || (letter == '/') || 
		(letter == '=') || (letter == -1)){
		return 0;
	}
	else {
		return 1;
	}
}

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name: %s\n", argv[1]);
		return -1;
	}
	char * inputFileName = argv[1];
	FILE * inputFile = fopen(inputFileName, "rb");
	
	char * fileName	= calloc(strlen(inputFileName) + 5, sizeof(char));
	
	for (int i = 0; i < strlen(argv[1]); i++){		//закинуть это в отдельную функцию
		fileName[i] = argv[1][i];
	}
	fileName[strlen(argv[1])] = '.';
	fileName[strlen(argv[1]) + 1] = 'o';
	fileName[strlen(argv[1]) + 2] = 'r';
	fileName[strlen(argv[1]) + 3] = 'i';
	fileName[strlen(argv[1]) + 4] = 'g';
	FILE * outputFile = fopen(fileName, "w");

	int currentLetters[4];

	while(EOF != currentLetters[0] && '=' != currentLetters[2] && '=' != currentLetters[3]){
		int letterAmount = 0;
		currentLetters[0] = fgetc(inputFile);
		if (base64Check(currentLetters[0])){ //можно закинуть в цикл
			free(fileName);
			fclose(inputFile);
			fclose(outputFile);
			printf("\nError: Wrong format.\n");
			return -1;
		}
		if (EOF != currentLetters[0]){
			currentLetters[1] = fgetc(inputFile);
			if (base64Check(currentLetters[1])){
				free(fileName);
				fclose(inputFile);
				fclose(outputFile);
				printf("\nError: Wrong format.\n");
				return -1;
			}
			
			if (EOF != currentLetters[1]){
				letterAmount++;
				currentLetters[2] = fgetc(inputFile);
				if (base64Check(currentLetters[2])){
					free(fileName);
					fclose(inputFile);
					fclose(outputFile);
					printf("\nError: Wrong format.\n");
					return -1;
				}
				
				if (EOF != currentLetters[2] && '=' != currentLetters[2]){
					letterAmount++;
					currentLetters[3] = fgetc(inputFile);
					if (base64Check(currentLetters[3])){
						free(fileName);
						fclose(inputFile);
						fclose(outputFile);
						printf("\nError: Wrong format.\n");
						return -1;
					}
					
					if (EOF != currentLetters[3] && '=' != currentLetters[3]){
						letterAmount++;
					}
				}
			}
			char output[3] = {0};
			decryp(currentLetters, output);
			for (int i = 0; i < letterAmount; i++){
				//printf("%c", output[i]);
				fprintf(outputFile, "%c", output[i]);
			}
		}
	}
		
	
	printf("\n");
	free(fileName);
	fclose(inputFile);
	fclose(outputFile);
}