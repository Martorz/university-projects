#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ALIVECELL 'o'
#define DEADCELL ' '

struct gameInfo {
	int xAxisSize, yAxisSize;
	int ruleB[10];
	int ruleS[10];
	int * ruleSize;
};

void fieldOutput(struct gameInfo gInfo, char **field){
	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			printf("[%c]", field[i][j]);
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
	/*int skipTheLine;
	if (xPosition == 0){
		for(int i = yPosition - 1; i <= yPosition + 1; i++){
			for(int j = xPosition; j <= xPosition + 1; j++){
				if (field[(i + yAxisSize) % yAxisSize][j] == ALIVECELL)	{
					countNeighbours++;
				}
				printf("x: %d, y: %d, val: %c\n", j, i, field[(i + yAxisSize) % yAxisSize][j]);
				skipTheLine = getchar();
			}
		}
	}
	else if (xPosition == xAxisSize){
		for(int i = yPosition - 1; i <= yPosition + 1; i++){
			for(int j = xPosition - 1; j <= xAxisSize - 1; j++){
				if (field[(i + yAxisSize) % yAxisSize][j] == ALIVECELL)	{
					countNeighbours++;
				}
				printf("x: %d, y: %d, val: %c\n", j, i, field[(i + yAxisSize) % yAxisSize][j]);
				skipTheLine = getchar();
			}
		}
	}
	else {
		for(int i = yPosition - 1; i <= yPosition + 1; i++){
			for(int j = xPosition - 1; j <= xPosition + 1; j++){
				if (field[(i + yAxisSize) % yAxisSize][j] == ALIVECELL)	{
					countNeighbours++;
				}
				printf("x: %d, y: %d, val: %c\n", j, i, field[(i + yAxisSize) % yAxisSize][j]);
				skipTheLine = getchar();
			}
		}
	}

	if (field[yPosition][yPosition] == ALIVECELL) countNeighbours--;
	printf("x: %d, y: %d, c: %d\n", xPosition, yPosition, countNeighbours);
	*/
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

char ** createNextGen(struct gameInfo gInfo, char **field) {
	char **newField;
	createArray(gInfo, &newField);
	int aliveNeighboursNumber = 0;

	for (int i = 0; i < gInfo.yAxisSize; i++) {
		for (int j = 0; j < gInfo.xAxisSize; j++) {
			aliveNeighboursNumber = checkAliveNeighbours(j, i, gInfo, field);
			
				if (field[i][j] == DEADCELL && matchingTheRuleB(aliveNeighboursNumber, gInfo.ruleB, gInfo.ruleSize[0]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRuleS(aliveNeighboursNumber, gInfo.ruleS, gInfo.ruleSize[1]) == 1) {
					newField[i][j] = ALIVECELL;
				}
				else if (field[i][j] == ALIVECELL && matchingTheRuleS(aliveNeighboursNumber, gInfo.ruleS, gInfo.ruleSize[1]) == 0) {
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
	gInfo.ruleSize = readRule(gInfo.ruleB, gInfo.ruleS, readingVar);

	char **field, **nextGen;
	int skipTheLine = 0;

	createArray(gInfo, &field);

	setTheFirstGen(field, inputFile);
	fclose(inputFile);
	fieldOutput(gInfo, field);

	nextGen = createNextGen(gInfo, field);
	while (areFieldsEqual(gInfo, field, nextGen) != 1) {
		field = nextGen;
		fieldOutput(gInfo, field);
		skipTheLine = getchar();
		nextGen = createNextGen(gInfo, field);
	}
	printf("The end.\n");
}
