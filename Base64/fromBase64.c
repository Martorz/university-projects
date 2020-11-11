#include <stdio.h>
#include <stddef.h>

const char alphabet[]/* = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/"*/;

char * decryp (unsigned char * input, size_t letterAmount){
	char * output;
	char temp[4]; //приходится использовать допольнительный массив, потому что символы не записываются в char*
	temp[0] = alphabet[(int)(input[0] >> 2)];
	if(letterAmount == 1){
		temp[1] = alphabet[(int)((input[0] & 3) << 4)];
		temp[2] = '=';
		temp[3] = '=';
	}
	else{
		temp[1] = alphabet[(int)(((input[0] & 3) << 4) | (input[1] >> 4))];
		if(letterAmount == 2) {
			temp[2] = alphabet[(int)((input[1] & 15) << 2)];
			temp[3] = '=';
		}
		else{
			temp[2] = alphabet[(int)(((input[1] & 15) << 2) | (input[2] >> 6))];
			temp[3] = alphabet[(int)(input[2] & 63)];
		}
	}
	output = temp;
	return output;
}

int main(int argc, char** argv){
	FILE * inputFile = fopen(argv[1], "rb");				//сделать проверку входной информации
	FILE * outputFile = fopen("output", "w");
	if (inputFile == NULL){
		printf("File reading error.\n");
		return -1;
	}
	unsigned char currentLetters[4];

	while(!feof(inputFile)){
		unsigned char c1, c2, c3, c4;
		//int letterAmount = fscanf(inputFile, "%c%c%c%c", &c1, &c2, &c3, &c4);
		//printf("%c %c %c %c\n", c1, c2, c3, c4);
		int letterAmount = fscanf(inputFile, "%c%c%c", currentLetters[1], currentLetters[2], currentLetters[3]);
		//printf("%c %c %c\n", currentLetters[1], currentLetters[2], currentLetters[3]);
		//printf("%d\n", letterAmount);
		/*currentLetters[0] = fgetc(inputFile);
		letterAmount++;
		if (!feof(inputFile)) {
			currentLetters[1] = fgetc(inputFile);
			letterAmount++;
			if (!feof(inputFile)) {
				currentLetters[2] = fgetc(inputFile);
				letterAmount++;
			}*/
		printf("%s", decryp(currentLetters, letterAmount));
	}

		//fprintf(outputFile, "%s", encryp(currentLetters));    --------------> как записывать в файл?
		//printf("%s ", currentLetters);
		
	

	//make char unsigned
	fclose(inputFile);
	fclose(outputFile);
}