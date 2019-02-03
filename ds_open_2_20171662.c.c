#include <stdio.h>
#include <stdlib.h>
#define COMPARE(x,y) (((x)>(y)) ? 1 : (((x) == (y)) ? 0 : -1 ))
#define MAX_TERMS 100
typedef struct {
	float coef;
	int expon;
} polynomial;
polynomial terms[MAX_TERMS];
int avail=0;
int start=0;

void padd(int, int, int, int, int*, int*);
void attach(float, int);
void readPoly(int*, int*, FILE*);
void printPoly(int*, int*);

int starta=0;
int startb=0;
int finisha=0;
int finishb=0;
int startd=0;
int finishd=0;


int main(void)
{
	int starta=0;
	int startb=0;
	int finisha=0;
	int finishb=0;
	int startd=0;
	int finishd=0;

	FILE *A = fopen("A.txt", "r");
	FILE *B = fopen("B.txt", "r");

	readPoly(&starta, &finisha, A);
	startb=finisha+1;
	readPoly(&startb, &finishb, B);
	padd(starta, finisha, startb, finishb, &startd, &finishd);
	printPoly(&startd, &finishd);

	return 0;
}

void padd(int starta, int finisha, int startb, int finishb, int *startd, int *finishd)
{ /* add A(x) and B(x) to obtain D(x) */
	float coefficient;
	*startd = avail;
	while(starta <= finisha && startb <= finishb)
		switch(COMPARE(terms[starta].expon, terms[startb].expon)) {
		case -1: /* a expon < b expon */ 						
			attach(terms[startb].coef, terms[startb].expon);
			startb++;
			break;
		case 0: /* equal exponents */
			coefficient = terms[starta].coef + 						
				terms[startb].coef;
			if(coefficient)
				attach(coefficient, terms[starta].expon);
			starta++; startb++;
			break;
		case 1: /* a expon > b expon */
			attach(terms[starta].coef, terms[starta].expon); 				
			starta++;
		}
	/* add in remaining terms of A(x) */
	for(; starta <= finisha; starta++)
		attach(terms[starta].coef, terms[starta].expon);
	/* add in remaining terms of B(x) */
	for(; startb <= finishb; startb++)
		attach(terms[startb].coef, terms[startb].expon);
	*finishd =avail-1;
}

void attach(float coefficient, int exponent)
{ /* add a new term to the polynomial */

	if(avail >= MAX_TERMS) {
		fprintf(stderr, "Too many terms in the polynomial");
		exit(1);
	}
	terms[avail].coef = coefficient;
	terms[avail++].expon = exponent;
}


void readPoly(int* starta, int* finisha, FILE* file)
{
	*starta=avail;
	*finisha=avail;

	int ex=0;
	float co=0;
	
	while(fscanf(file,"%f\t%d",&co, &ex)!=EOF)
	{
		attach(co, ex);
	}

	*finisha=avail-1;
}

void printPoly(int* starta, int* finisha)
{
	int i;

	for(i=*starta; i<=*finisha; i++)
	{
		printf("(%.0f,%d)", terms[i].coef, terms[i].expon);

		if(i!=*finisha)
			printf(", ");

		if(i==*finisha)
			printf("\n");
	}
	printf("\n");
}