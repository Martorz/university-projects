#include <stdio.h>
#include <stddef.h>

const char alphabet[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

void encryp (int * input, size_t letterAmount, char output[4]){
	output[0] = alphabet[(int)(input[0] >> 2)];
	if(letterAmount == 1){
		output[1] = alphabet[(int)((input[0] & 3) << 4)];
		output[2] = '=';
		output[3] = '=';
	}
	else{
		output[1] = alphabet[(int)(((input[0] & 3) << 4) | (input[1] >> 4))];
		if(letterAmount == 2) {
			output[2] = alphabet[(int)((input[1] & 15) << 2)];
			output[3] = '=';
		}
		else{
			output[2] = alphabet[(int)(((input[1] & 15) << 2) | (input[2] >> 6))];
			output[3] = alphabet[(int)(input[2] & 63)];
		}
	}
}

int main(int argc, char** argv){
	FILE * inputFile = fopen(argv[1], "rb");				//сделать проверку входной информации
	FILE * outputFile = fopen("output", "w");
	if (inputFile == NULL){
		printf("File reading error.\n");
		return -1;
	}
	int currentLetters[3];

	while(EOF != currentLetters[0]){
		int skipTheLine = 0;
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
			printf("%s", output);
		}
	}

		//fprintf(outputFile, "%s", encryp(currentLetters));    --------------> как записывать в файл?
		
	

	//make char unsigned
	printf("\n");
	fclose(inputFile);
	fclose(outputFile);
}