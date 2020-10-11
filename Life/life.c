#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIVECELL 'o'
#define DEADCELL ' '

void fieldOutput(int xAxisSize, int yAxisSize, char **field){
	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			printf("[%c]", field[i][j]);
	}
		printf("\n");
	}
	printf("\n");
}

void setTheFirstGen(int xAxisSize, char **field, FILE * inputFile) {
	int xToSet = 0, yToSet = 0, repeats = 1, isLastInt = 0;
	char readingVar = 0;
	while(readingVar != '!'){
		readingVar = fgetc(inputFile);
		if (readingVar >= '0' && readingVar <= '9') {
			if (isLastInt == 1){
				repeats = repeats * 10  + (readingVar - '0');
			}
			else {
				repeats = readingVar - '0';
			}
			isLastInt = 1;
		}
		else if (readingVar == 'b') {
			for(int i = 0; i < repeats; i++){
				xToSet += 1;
			}
			repeats = 1;
			isLastInt = 0;
		}
		else if (readingVar == 'o') {
			for(int i = 0; i < repeats; i++){
				field[yToSet][xToSet] = ALIVECELL;
				xToSet += 1;
			}
			repeats = 1;
			isLastInt = 0;
		}
		else if (readingVar == '$') {
			yToSet += 1;
			xToSet = 0;
			isLastInt = 0;
		}
	}
}

int checkAliveNeighbours(int xPosition, int yPosition, int xAxisSize, int yAxisSize, char **field) {
	int countNeighbours = 0;
	xAxisSize -= 1;
	yAxisSize -= 1;
	if (xPosition == 0 && yPosition == 0) { //upper left corner
		if (field[yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == xAxisSize && yPosition == 0) { //upper right corner
		if (field[yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == 0 && yPosition == yAxisSize) { //down left corner
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == xAxisSize && yPosition == yAxisSize) { //down right corner
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (yPosition == 0 && xPosition != xAxisSize && xPosition != 0) { //upper border
		if (field[yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (yPosition == yAxisSize && xPosition != xAxisSize && xPosition != 0) { //lower border
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yAxisSize - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == 0 && yPosition != yAxisSize && yPosition != 0) { //left border
		if (field[yPosition - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == xAxisSize && yPosition != yAxisSize && yPosition != 0) { //right border
		if (field[yPosition - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition != 0 && xPosition != xAxisSize && yPosition != yAxisSize && yPosition != 0) { //middle space
		if (field[yPosition - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	return countNeighbours;
}

int areFieldsEqual(int xAxisSize, int yAxisSize, char **oldField, char **newField) {
	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			if (oldField[i][j] != newField[i][j]) {
				return 0;
			}
	}
	}
	return 1;
}

void createArray(int xAxisSize, int yAxisSize, char ***field) {
	*field = calloc(yAxisSize, sizeof(char*));

	for (int i = 0; i < yAxisSize; i++) {
		(*field)[i] = calloc(xAxisSize, sizeof(char));
	}

	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			(*field)[i][j] = DEADCELL;
	}
	}
}

int matchingTheRuleB(int aliveCells, int ruleB[], int ruleSize){
	for(int i = 0; i < ruleSize; i++){
		if (aliveCells == ruleB[i]){
			return 1;
		}
	}
	return 0;
}

int matchingTheRuleS(int aliveCells, int ruleS[], int ruleSize){
	for(int i = 0; i < ruleSize; i++){
		if (aliveCells == ruleS[i]){
			return 1;
		}
	}
	return 0;
}

char ** createNextGen(int xAxisSize, int yAxisSize, char **field, int ruleB[], int ruleS[], int * ruleSize) {
	char **newField;
	createArray(xAxisSize, yAxisSize, &newField);
	int aliveNeighboursNumber = 0;

	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			aliveNeighboursNumber = checkAliveNeighbours(j, i, xAxisSize, yAxisSize, field);
			
				if (field[i][j] == DEADCELL && matchingTheRuleB(aliveNeighboursNumber, ruleB, ruleSize[0]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRuleS(aliveNeighboursNumber, ruleS, ruleSize[1]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRuleS(aliveNeighboursNumber, ruleS, ruleSize[1]) == 0) {
					newField[i][j] = DEADCELL;
				}
	}
	}
	return newField;
}

int convertToInt(char word[]){
	int number = 0;
	for(int i = 0; i < strlen(word); i++){
		if (word[i] >= '0' && word[i] <= '9') {
			number = number * 10 + (word[i] - '0');
		}
	}
	return number;
}

int * readRule(int B[], int S[], char word[]) {
	int i = 1, j = 0;
	int *ruleSize = calloc(2, sizeof(int));
	while(word[i] != '/'){
		B[j] = word[i] - '0';
		j++;
		i++;
		ruleSize[0]++;
	}
	i += 2;
	j = 0;
	while(i != strlen(word)){
	//for(int k = i; k < strlen(word); k++){
		S[j] = word[i] - '0';
		j++;
		i++;
		ruleSize[1]++;
	}
	return ruleSize;
}

int main(int argc, char** argv){
	FILE *inputFile = fopen(argv[1], "r");
	if (inputFile == NULL) {
		printf("File reading error.\n");
		return -1;
	}
	int xAxisSize = 0, yAxisSize = 0;
	int ruleB[10], ruleS[10];
	int * ruleSize;
	char readingVar[255];
	while(strcmp(readingVar, "rule") != 0){
		if (readingVar[0] == '#') {
		}
		else if (strcmp(readingVar, "x") == 0) {
			fscanf(inputFile, "%s", readingVar);
			fscanf(inputFile, "%s", readingVar);
			xAxisSize = convertToInt(readingVar);
		}
		else if (strcmp(readingVar, "y") == 0){
			fscanf(inputFile, "%s", readingVar);
			fscanf(inputFile, "%s", readingVar);
			yAxisSize = convertToInt(readingVar);
		}
		fscanf(inputFile, "%s", readingVar);
	}
	fscanf(inputFile, "%s", readingVar);
	fscanf(inputFile, "%s", readingVar);
	ruleSize = readRule(ruleB, ruleS, readingVar);

	char **field, **nextGen;
	int skipTheLine = 0;

	createArray(xAxisSize, yAxisSize, &field);

	setTheFirstGen(xAxisSize, field, inputFile);
	fclose(inputFile);
	fieldOutput(xAxisSize, yAxisSize, field);

	nextGen = createNextGen(xAxisSize, yAxisSize, field, ruleB, ruleS, ruleSize);
	while (areFieldsEqual(xAxisSize, yAxisSize, field, nextGen) != 1) {
		field = nextGen;
		fieldOutput(xAxisSize, yAxisSize, field);
		skipTheLine = getchar();
		nextGen = createNextGen(xAxisSize, yAxisSize, field, ruleB, ruleS, ruleSize);
	}
	printf("The end.\n");
}
