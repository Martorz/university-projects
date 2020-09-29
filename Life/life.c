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
	int xToSet, yToSet;
	int coordinats[8][2] = {{1, 1}, {2, 1}, {3, 1}, {1, 2}, {2, 2}, {1, 3}, {2, 3}, {3, 3}};
	for (int i = 0; i < 8; i++) {
		xToSet = coordinats[i][1];
		yToSet = coordinats[i][0];

		field[yToSet][xToSet] = ALIVECELL;
	}
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
	}
	else if (xPosition == xAxisSize && yPosition == 0) { //upper right corner
		if (field[yAxisSize][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
	}
	else if (xPosition == 0 && yPosition == yAxisSize) { //down left corner
		if (field[0][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
	}
	else if (xPosition == xAxisSize && yPosition == yAxisSize) { //down right corner
		if (field[0][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[0][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yAxisSize - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;	
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
	}
	else if (xPosition == 0 && yPosition != yAxisSize && yPosition != 0) { //left border
		if (field[yPosition - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition + 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition + 1] == ALIVECELL) countNeighbours += 1;
	}
	else if (xPosition == xAxisSize && yPosition != yAxisSize && yPosition != 0) { //right border
		if (field[yPosition - 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition - 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition][xPosition - 1] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition] == ALIVECELL) countNeighbours += 1;
		if (field[yPosition + 1][xPosition - 1] == ALIVECELL) countNeighbours += 1;
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

char ** createNextGen(int xAxisSize, int yAxisSize, char **field) {
	char **newField;
	createArray(xAxisSize, yAxisSize, &newField);
	int aliveNeighboursNumber;

	for (int i = 0; i < yAxisSize; i++) {
		for (int j = 0; j < xAxisSize; j++) {
			aliveNeighboursNumber = checkAliveNeighbours(j, i, xAxisSize, yAxisSize, field);
			//printf("y: %d, x: %d, num: %d, old_cell: %c, ", i, j, aliveNeighboursNumber, field[i][j]);
			
				if (field[i][j] == DEADCELL && aliveNeighboursNumber == 3) 
					newField[i][j] = ALIVECELL;
				else if (field[i][j] == ALIVECELL && (aliveNeighboursNumber == 3 || aliveNeighboursNumber == 2)) 
					newField[i][j] = ALIVECELL;
				else if (field[i][j] == ALIVECELL && (aliveNeighboursNumber > 3 || aliveNeighboursNumber < 2))
					newField[i][j] = DEADCELL;
			
			//printf("newcell: %c\n", newField[i][j]);
	}
	}
	return newField;
}

int main(){
	int xAxisSize = XSIZE, yAxisSize = YSIZE;
	char **field, **nextGen;
	int skipTheLine;

	createArray(xAxisSize, yAxisSize, &field);

	setTheFirstGen(xAxisSize, field);
	fieldOutput(xAxisSize, yAxisSize, field);

	nextGen = createNextGen(xAxisSize, yAxisSize, field);
	while (areFieldsEqual(xAxisSize, yAxisSize, field, nextGen) != 1) {
		field = nextGen;
		fieldOutput(xAxisSize, yAxisSize, field);
		skipTheLine = getchar();
		nextGen = createNextGen(xAxisSize, yAxisSize, field);
	}
	printf("The end.\n");
}
