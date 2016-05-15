#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MAX_Y 40
#define MAX_X 53

int getRandomStep();
int takeRandomStep(int *board, int *currentX, int *currentY);
void printBoard(int *board, long unsigned arrSize);
void makeBoard(int *board, long unsigned arrSize);
int* getCharAt(int *board, int x, int y); 

int main(void) {
	int arr[MAX_Y][MAX_X];
	int *board = &arr[0][0];
	int currentX = MAX_X/2;
	int currentY = MAX_Y/2;

	srand((unsigned int) time(NULL));
	makeBoard(board, sizeof arr);
	while (takeRandomStep(board, &currentY, &currentX)); 
	printBoard(board, sizeof arr);
	return 0;
}

void makeBoard(int *board, long unsigned arrSize) {
	int i = 0;
	for (i = 0; i < arrSize/sizeof(*board); i++) 
			*(board + i) = '.';
}

int* getCharAt(int *board, int x, int y) {
	return &(*(board + (y * (MAX_X)) + x));
}


void printBoard(int *board, long unsigned arrSize) {
	int i = 0;
	for (i = 0; i < arrSize/sizeof(*board); i++) {
		  if (i != 0 && i % MAX_X == 0) printf("\n");
			printf("%c ", *(board + i));
	}
	printf("\n");
}

int getRandomStep() {
	return rand() % 4;
}

int takeRandomStep(int *board, int *currentY, int *currentX) {
	int blocked = 0;	
	int step = getRandomStep();
	switch (step) {
start:
		case 0:
			if (*currentX - 1 >= 0 && 
					*getCharAt(board, *currentX - 1, *currentY) == '.') {
				*currentX -= 1;
				break;
			}
		case 1:
			if (*currentX + 1 < MAX_X && 
					*getCharAt(board, *currentX + 1, *currentY) == '.') {
				*currentX += 1;
				break;
			}
		case 2:
			if (*currentY + 1 < MAX_Y && 
					*getCharAt(board, *currentX, *currentY + 1) == '.') {
				*currentY += 1;
				break;
			}
		case 3:
			if (*currentY - 1 >= 0 && 
					*getCharAt(board, *currentX, *currentY - 1) == '.') {
				*currentY -= 1;
				break;
			}
		default:
			if (blocked == 1) return 0;
			blocked = 1;
			goto start;
	}

	*(board + (*currentX + (*currentY * MAX_X))) = 'x';
	return 1;
}
