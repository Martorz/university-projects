#include <stdio.h>
#include <stddef.h>
#include <string.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
const int formatNumber = 255;

void decryp (int * input, size_t letterAmount, char output[3]){
	int origLetter[4];
	origLetter[0] = strchr(alphabet, (char)input[0]) - alphabet;
	origLetter[1] = strchr(alphabet, (char)input[1]) - alphabet;
	origLetter[2] = strchr(alphabet, (char)input[2]) - alphabet;
	origLetter[3] = strchr(alphabet, (char)input[3]) - alphabet;
	output[0] = (char)((origLetter[0] << 2) | (origLetter[1] >> 4));
	output[1] = (char)(((origLetter[1] << 4) & formatNumber) | (origLetter[2] >> 2));
	output[2] = (char)(((origLetter[2] << 6) & formatNumber) | origLetter[3]);
}

int main(int argc, char** argv){
	FILE * inputFile = fopen(argv[1], "rb");				//сделать проверку входной информации
	FILE * outputFile = fopen("output", "w");
	if (inputFile == NULL){
		printf("File reading error.\n");
		return -1;
	}
	int currentLetters[4];

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
					currentLetters[3] = fgetc(inputFile);
					
					if (EOF != currentLetters[3]){
						letterAmount++;
					}
				}
			}
			char output[3] = {0};
			decryp(currentLetters, letterAmount, output);
			//printf("%d %d %d %d\n", currentLetters[0], currentLetters[1], currentLetters[2], currentLetters[3]);
			printf("%c %c %c ", output[0], output[1], output[2]);
			//fprintf(outputFile, "%s", output);
		}
	}

		//fprintf(outputFile, "%s", encryp(currentLetters));    --------------> как записывать в файл?
		//printf("%s ", currentLetters);
		
	

	printf("\n");
	fclose(inputFile);
	fclose(outputFile);
}