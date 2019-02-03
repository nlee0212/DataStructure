#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define TRUE true
#define FALSE false

#define M 103
#define P 103
#define MAX_DIRECTION_SIZE 8
#define MAX_STACK_SIZE M * P

#define _MDH_DEBUG_

/* Structure definition  */
typedef struct{
	short int row;
	short int col;
	short int dir;
}element;

typedef struct{
	short int vert;
	short int horiz;
}offsets;

/* Global Variables Region */
char maze[M][P];
char mark[M][P];
offsets move[MAX_DIRECTION_SIZE]={{-1,0}, {-1,1}, {0,1}, {1,1},
	{1,0}, {1,-1}, {0,-1}, {-1,-1}};
int EXIT_ROW, EXIT_COL;
/* Stack */
element stack[MAX_STACK_SIZE];
int top;

/* Functions to be implemented */
element pop();
void push(element item);
void path();

/* Functions already implemented by MDH*/
void PrintMaze();
void ReadMaze();

/* main Function */
int main()
{
	ReadMaze();
	//PrintMaze();

	path();

	return 0;
}

void ReadMaze()
{
	FILE* _read_fp = fopen("maze.txt","r");
	char _buf[M];
	int i;

	/* File Validation Check */
	if( !_read_fp ){ 
		fprintf(stderr, "■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be Shutdown\n");
		fprintf(stderr, "■■■■■■■■■■■■■■■■■■■■■■■■■\n");
		exit(0);
	}
	
	/* Scanning Input */
	fscanf(_read_fp, "%d %d", &EXIT_ROW, &EXIT_COL);
	for( i=1 ; i<= EXIT_ROW ;i++){
		fscanf(_read_fp, "%s",&maze[i][1]);
	}
	
	/* Enveloping maze in '1' which indicates artificial wall */
	for( i=0 ; i<=EXIT_COL + 1 ; i++){
		maze[0][i]='1';
		maze[EXIT_ROW+1][i]='1';
	}
	for( i=0 ; i<=EXIT_ROW + 1 ; i++){
		maze[i][0]='1';
		maze[i][EXIT_COL+1]='1';
	}
	fclose(_read_fp);

}


void PrintMaze()
{
	int i, j;
#ifdef _MDH_DEBUG_
	printf("Input Checking\n");
	printf("%d %d\n",EXIT_ROW, EXIT_COL);
#endif
	for( i=0 ; i <= EXIT_ROW+1 ; i++)
	{
		printf("%s\n",maze[i]);
	}
}


element pop()
{
	/* return the top element from the stack */
	if (top == -1)
		exit(-1); /* return an error key */
	
	return stack[top--];


}

void push(element item)
{
	/* add an item to the global stack */
	if (top >= MAX_STACK_SIZE - 1)
		printf("ERROR : Stack is full!\n");
	
	
	stack[++top] = item;
}

void path()
{
	/* output a path through the maze if such a path exists */
	int i, row, col, nextRow, nextCol, dir, found = FALSE;
	element position;
	mark[1][1] = 1; top = 0;
	stack[0].row = 1; stack[0].col = 1; stack[0].dir = 1;

	while (top > -1 && !found) 
	{
		position = pop();		//current position
		row = position.row; col = position.col, dir = position.dir;

		while (dir < 8 && !found) {
			/* move in direction dir */
			nextRow = row + move[dir].vert;
			nextCol = col + move[dir].horiz;

			if (nextRow == EXIT_ROW && nextCol == EXIT_COL) 
				found = TRUE;		//end of maze


			else if (maze[nextRow][nextCol] == '0' && !mark[nextRow][nextCol]) 
			{		//move to new dir
				mark[nextRow][nextCol] = 1;			//mark new pos
				position.row = row; 
				position.col = col;
				position.dir = ++dir;
				push(position);
				row = nextRow; col = nextCol; dir = 0;
			}
			else ++dir;
		}
	}
	if (found) {
		printf("The path is : \n");
		printf("row   col \n");
		for (i = 0; i <= top; i++)
			printf("%2d %5d\n", stack[i].row, stack[i].col);
		printf("%2d %5d\n", row, col);
		printf("%2d %5d\n", EXIT_ROW, EXIT_COL);
	}
	else printf("The maze does not have a path.\n");
}


