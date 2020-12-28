#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIVECELL 1
#define DEADCELL 0
#define ALIVECELL_VIEW 'o'
#define DEADCELL_VIEW ' '

struct gameInfo {
	size_t xAxisSize;
	size_t yAxisSize;
	int ruleB[10];
	int ruleS[10];
	int ruleSize[2];
};

void fieldOutput(struct gameInfo gInfo, char **field){
	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			if (field[i][j] == ALIVECELL) {
				printf("[%c]", ALIVECELL_VIEW);
			}
			else {
				printf("[%c]", DEADCELL_VIEW);
			}
	}
		printf("\n");
	}
	printf("\n");
}

void setTheFirstGen(char **field, FILE * inputFile) {
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

int checkAliveNeighbours(int xPosition, int yPosition, struct gameInfo gInfo, char **field) {
	int countNeighbours = 0;
	gInfo.xAxisSize -= 1;
	gInfo.yAxisSize -= 1;
	
	if (xPosition == 0 && yPosition == 0) { //upper left corner
		if (field[gInfo.yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == gInfo.xAxisSize && yPosition == 0) { //upper right corner
		if (field[gInfo.yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == 0 && yPosition == gInfo.yAxisSize) { //down left corner
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == gInfo.xAxisSize && yPosition == gInfo.yAxisSize) { //down right corner
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (yPosition == 0 && xPosition != gInfo.xAxisSize && xPosition != 0) { //upper border
		if (field[gInfo.yAxisSize][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (yPosition == gInfo.yAxisSize && xPosition != gInfo.xAxisSize && xPosition != 0) { //lower border
		if (field[0][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[0][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[gInfo.yAxisSize - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == 0 && yPosition != gInfo.yAxisSize && yPosition != 0) { //left border
		if (field[yPosition - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition == gInfo.xAxisSize && yPosition != gInfo.yAxisSize && yPosition != 0) { //right border
		if (field[yPosition - 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition] == ALIVECELL) { countNeighbours += 1; }
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) { countNeighbours += 1; }
	}
	else if (xPosition != 0 && xPosition != gInfo.xAxisSize && yPosition != gInfo.yAxisSize && yPosition != 0) { //middle space
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

int areFieldsEqual(struct gameInfo gInfo, char **oldField, char **newField) {
	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			if (oldField[i][j] != newField[i][j]) {
				return 0;
			}
	}
	}
	return 1;
}

void createArray(struct gameInfo gInfo, char ***field) {
	*field = calloc(gInfo.yAxisSize, sizeof(char*));

	for (int i = 0; i < gInfo.yAxisSize; i++) {
		(*field)[i] = calloc(gInfo.xAxisSize, sizeof(char));
	}

	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			(*field)[i][j] = DEADCELL;
	}
	}
}

int matchingTheRule(int aliveCells, int rule[], int ruleSize){
	for(int i = 0; i < ruleSize; i++){
		if (aliveCells == rule[i]){
			return 1;
		}
	}
	return 0;
}

char ** createNextGen(struct gameInfo gInfo, char **field) {
	char **newField;
	createArray(gInfo, &newField);
	int aliveNeighboursNumber = 0;

	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			aliveNeighboursNumber = checkAliveNeighbours(j, i, gInfo, field);
			
				if (field[i][j] == DEADCELL && matchingTheRule(aliveNeighboursNumber, gInfo.ruleB, gInfo.ruleSize[0]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRule(aliveNeighboursNumber, gInfo.ruleS, gInfo.ruleSize[1]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRule(aliveNeighboursNumber, gInfo.ruleS, gInfo.ruleSize[1]) == 0) {
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

void readRule(int B[], int S[], char word[], int ruleSize[]) {
	int i = 1, j = 0;
	ruleSize[0] = 0;
	ruleSize[1] = 0;
	while(word[i] != '/'){
		B[j] = word[i] - '0';
		j++;
		i++;
		ruleSize[0]++;
	}
	i += 2;
	j = 0;
	while(i != strlen(word)){
		S[j] = word[i] - '0';
		j++;
		i++;
		ruleSize[1]++;
	}
}

int fileExist(char * fileName) {
	FILE * input;
    if (input = fopen(fileName, "r")){
        fclose(input);
        return 1;
    }
    return 0;
}

int main(int argc, char** argv){
	if (argv[1] == NULL){
		printf("Error: File reading error. File name is missing.\n");
		return -1;
	}

	if (fileExist(argv[1]) == 0) {
		printf("Error: Invalid file name. File name: %s\n", argv[1]);
		return -1;
	}

	if (argc != 2) {
		printf("Error: Too many arguments. All the excess arguments will be ignored.\n");
	}

	char * inputFileName = argv[1];
	FILE * inputFile = fopen(inputFileName, "r");
	
	struct gameInfo gInfo;
	gInfo.xAxisSize = 0, gInfo.yAxisSize = 0;

	char readingVar[255];
	while(strcmp(readingVar, "rule") != 0){
		if (readingVar[0] == '#') {
			while (readingVar[0] != '\n') {
				readingVar[0] = fgetc(inputFile);
			}
		}
		else if (strcmp(readingVar, "x") == 0) {
			fscanf(inputFile, "%s", readingVar);
			fscanf(inputFile, "%s", readingVar);
			gInfo.xAxisSize = convertToInt(readingVar);
		}
		else if (strcmp(readingVar, "y") == 0){
			fscanf(inputFile, "%s", readingVar);
			fscanf(inputFile, "%s", readingVar);
			gInfo.yAxisSize = convertToInt(readingVar);
		}
		fscanf(inputFile, "%s", readingVar);
	}
	fscanf(inputFile, "%s", readingVar);
	fscanf(inputFile, "%s", readingVar);
	readRule(gInfo.ruleB, gInfo.ruleS, readingVar, gInfo.ruleSize);

	char **field, **nextGen;
	int skipTheLine = 0;

	createArray(gInfo, &field);

	setTheFirstGen(field, inputFile);
	fclose(inputFile);
	fieldOutput(gInfo, field);

	nextGen = createNextGen(gInfo, field);
	while (areFieldsEqual(gInfo, field, nextGen) != 1) {
		for (int i = 0; i < gInfo.yAxisSize; i++) {
			free(field[i]);
		}
		free(field);
		field = nextGen;
		fieldOutput(gInfo, field);
		skipTheLine = getchar();
		nextGen = createNextGen(gInfo, field);
		
	}
	for (int i = 0; i < gInfo.yAxisSize; i++) {
		free(nextGen[i]);
	}
	free(nextGen);

	for (int i = 0; i < gInfo.yAxisSize; i++) {
		free(field[i]);
	}
	free(field);
	

	printf("The end.\n");
}
