#include <stdio.h>
#include <stdlib.h>

#define XSIZE 5
#define YSIZE 5
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

void setTheFirstGen(int xAxisSize, char **field) {
	printf("Setting the first generation. Enter X and Y. Enter \" E \" to finish.\n");

	char input[30];
	int xToSet, yToSet;
	int coordinats[8][2] = {{1, 1}, {2, 1}, {3, 1}, {1, 2}, {2, 2}, {1, 3}, {2, 3}, {3, 3}};
	//int coordinats[8][2] = {{4, 4}, {5, 4}, {6, 4}, {4, 5}, {5, 5}, {6, 5}, {4, 6}, {6, 6}};
	for (int i = 0; i < 8; i++) {
		xToSet = coordinats[i][0];
		yToSet = coordinats[i][1];

		field[yToSet][xToSet] = ALIVECELL;
	}
	/*scanf("%s", input);
	while (input[0] != 'E') {// 		--> understand how to make it stop on 0
		//								--> how to add space between nums	
		//								!! make a check !!
		xToSet = input[0] - '0';
		yToSet = input[1] - '0';

		field[yToSet][xToSet] = ALIVECELL;

		scanf("%s", input);
	}*/
}

int checkAliveNeighbours(int xPosition, int yPosition, int xAxisSize, int yAxisSize, char **field) {
	int countNeighbours = 0;
	xAxisSize -= 1;
	yAxisSize -= 1;
	if (xPosition == 0 && yPosition == 0) { //upper left corner
		if (field[yAxisSize][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		//printf("[x][ ][ ]\n[ ][ ][ ]\n[ ][ ][ ]\n\n");
	}
	else if (xPosition == xAxisSize && yPosition == 0) { //upper right corner
		if (field[yAxisSize][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][x]\n[ ][ ][ ]\n[ ][ ][ ]\n\n");
	}
	else if (xPosition == 0 && yPosition == yAxisSize) { //down left corner
		if (field[0][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][ ]\n[ ][ ][ ]\n[x][ ][ ]\n\n");
	}
	else if (xPosition == xAxisSize && yPosition == yAxisSize) { //down right corner
		if (field[0][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;	
		//printf("[ ][ ][ ]\n[ ][ ][ ]\n[ ][ ][x]\n\n");
	}
	else if (yPosition == 0 && xPosition != xAxisSize && xPosition != 0) { //upper border
		if (field[yAxisSize][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][x][ ]\n[ ][ ][ ]\n[ ][ ][ ]\n\n");
	}
	else if (yPosition == yAxisSize && xPosition != xAxisSize && xPosition != 0) { //lower border
		if (field[0][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][ ]\n[ ][ ][ ]\n[ ][x][ ]\n\n");
	}
	else if (xPosition == 0 && yPosition != yAxisSize && yPosition != 0) { //left border
		if (field[yPosition - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][ ]\n[x][ ][ ]\n[ ][ ][ ]\n\n");
	}
	else if (xPosition == xAxisSize && yPosition != yAxisSize && yPosition != 0) { //right border
		if (field[yPosition - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][ ]\n[ ][ ][x]\n[ ][ ][ ]\n\n");
	}
	else if (xPosition != 0 && xPosition != xAxisSize && yPosition != yAxisSize && yPosition != 0) { //middle space
		if (field[yPosition - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		//printf("[ ][ ][ ]\n[ ][x][ ]\n[ ][ ][ ]\n\n");
	}
	return countNeighbours;
}

int areFieldsEqual(int xAxisSize, int yAxisSize, char **oldField, char **newField) {
	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			if (oldField[i][j] != newField[i][j]) 
				return 0;
	}
	}
	return 1;
}

void createArray(int xAxisSize, int yAxisSize, char ***field) {
	*field = calloc(xAxisSize, sizeof(char*));

	for (int i = 0; i < xAxisSize; i++) {
		(*field)[i] = calloc(yAxisSize, sizeof(char));
	}

	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			(*field)[i][j] = DEADCELL;
	}
	}
}

char ** createNextGen(int xAxisSize, int yAxisSize, char **field) {
	char **newField;
	createArray(xAxisSize, yAxisSize, &newField);
	int aliveNeighboursNumber;

	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			aliveNeighboursNumber = checkAliveNeighbours(i, j, xAxisSize, yAxisSize, field);
			if (field[i][j] == DEADCELL && aliveNeighboursNumber == 3) 
				newField[i][j] = ALIVECELL;
			else if (field[i][j] == ALIVECELL && (aliveNeighboursNumber == 3 || aliveNeighboursNumber == 2)) 
				newField[i][j] = ALIVECELL;
			else if (field[i][j] == ALIVECELL && (aliveNeighboursNumber > 3 || aliveNeighboursNumber < 2))
				newField[i][j] = DEADCELL;

			//printf("y: %d, x: %d, num: %d, cell: %c\n", i, j, aliveNeighboursNumber, newField[i][j]);
	}
	}
	return newField;
}

int main(){
	int xAxisSize = XSIZE, yAxisSize = YSIZE;
	char **field, **nextGen;
	int skipTheLine;

	createArray(xAxisSize, yAxisSize, &field);

	fieldOutput(xAxisSize, yAxisSize, field);
	printf("\n");

	setTheFirstGen(xAxisSize, field);
	fieldOutput(xAxisSize, yAxisSize, field);

	nextGen = createNextGen(xAxisSize, yAxisSize, field);
	//for (int i = 0; i < 1; i++) {
	while (areFieldsEqual(xAxisSize, yAxisSize, field, nextGen) != 1) {
		field = nextGen;
		fieldOutput(xAxisSize, yAxisSize, field);
		skipTheLine = getchar();
		nextGen = createNextGen(xAxisSize, yAxisSize, field);
	}
	printf("The end.\n");
}
