#include <stdio.h>
#include <stddef.h>
#include <string.h>
#include <stdlib.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const int formatNumber = 255;
const int equalSignCode = 61;

void decryp (int * input, char output[3]){
	int origLetter[4];
	origLetter[0] = strchr(alphabet, (char)input[0]) - alphabet;
	origLetter[1] = strchr(alphabet, (char)input[1]) - alphabet;
	output[0] = (char)((origLetter[0] << 2) | (origLetter[1] >> 4));
	if(input[2] != equalSignCode) {
		origLetter[2] = strchr(alphabet, (char)input[2]) - alphabet;
		output[1] = (char)(((origLetter[1] << 4) & formatNumber) | (origLetter[2] >> 2));
		if(input[3] != equalSignCode) {
			origLetter[3] = strchr(alphabet, (char)input[3]) - alphabet;
			output[2] = (char)(((origLetter[2] << 6) & formatNumber) | origLetter[3]);
		}
	}
	
	
}

int main(int argc, char** argv){
	FILE * inputFile = fopen(argv[1], "rb");				//сделать проверку входной информации
	if (inputFile == NULL){
		printf("File reading error.\n");
		return -1;
	}
	char * fileName	= calloc(strlen(argv[1]) + 5, sizeof(char)); 	//освободить память
	
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

	while(EOF != currentLetters[0] && equalSignCode != currentLetters[2] && equalSignCode != currentLetters[3]){
		int letterAmount = 0;
		currentLetters[0] = fgetc(inputFile);


		if (EOF != currentLetters[0]){
			currentLetters[1] = fgetc(inputFile);
			
			if (EOF != currentLetters[1]){
				letterAmount++;
				currentLetters[2] = fgetc(inputFile);
				
				if (EOF != currentLetters[2] && equalSignCode != currentLetters[2]){
					letterAmount++;
					currentLetters[3] = fgetc(inputFile);
					
					if (EOF != currentLetters[3] && equalSignCode != currentLetters[3]){
						letterAmount++;
					}
				}
			}
			char output[3] = {0};
			decryp(currentLetters, output);
			for (int i = 0; i < letterAmount; i++){
				printf("%c", output[i]);
				fprintf(outputFile, "%c", output[i]);
			}
		}
	}
		
	

	printf("\n");
	fclose(inputFile);
	fclose(outputFile);
}