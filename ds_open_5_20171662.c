#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPR_SIZE 1000

typedef enum { lparen, rparen, plus, minus, times, divide, mod, eos, operand } precedence;
precedence token;
char expr[MAX_EXPR_SIZE];
static int isp[] = { 0, 19, 12, 12, 13, 13, 13, 0 };
static int icp[] = { 20, 19, 12, 12, 13, 13, 13, 0 };

typedef struct Node
{
	precedence data;
	struct Node *next;
}Node;

Node *top1 = NULL;

void readExpr(FILE* _fp, char* _expr);
void push(precedence  n);
void printToken(precedence n);
void postfix();


int main()
{
	FILE* readfp = fopen("input.txt", "r");

	readExpr(readfp, expr);
	postfix();

	fclose(readfp);
	return 0;
}

void readExpr(FILE* _fp, char* _expr)
{

	if (!_fp) {
		fprintf(stderr, "Input file doesn't exist\n");
		fprintf(stderr, "Program will be shutdown\n");
		exit(0);
	}

	fscanf(_fp, "%s", _expr);

	fclose(_fp);
}

void postfix()
{
	char symbol;
	int n = 0;
	int top = 0;

	top1 = (Node*)malloc(sizeof(Node));
	top1->data = eos;

	for (token = getToken(&symbol, &n); token != eos; token = getToken(&symbol, &n))
	{

		if (token == operand)
			printf("%c", symbol);

		else if (token == rparen)
		{
			while (top1->data != lparen)
				printToken(pop());
			pop();
		}

		else {
			while (isp[top1->data] >= icp[token])
				printToken(pop());
			push(token);
		}
	}

	while ((token = pop()) != eos)
		printToken(token);
	printf("\n");
}

precedence getToken(char* symbol, int* n)
{
	*symbol = expr[(*n)++];
	switch (*symbol) {
	case '(': return lparen;
	case ')': return rparen;
	case '+': return plus;
	case '-': return minus;
	case '/': return divide;
	case '*': return times;
	case '%': return mod;
	case '\0': return eos;
	default: return operand; 
	}
}



void printToken(precedence n)
{
	switch (n) 
	{
	case times: printf("*"); break;
	case plus:  printf("+"); break;
	case minus: printf("-"); break;
	case divide: printf("/"); break;
	case mod: printf("%"); break;
	}
}

precedence pop()
{
	if (top1 == NULL) 
	{
		printf("\nStack is Empty!!!\n");
		return eos;
	}

	else 
	{
		precedence n;
		Node *temp;
		temp = (Node*)malloc(sizeof(Node));
		temp = top1;
		top1 = temp->next;
		n = temp->data;
		free(temp);
		return n;
	}
}


void push(precedence n)
{
	Node *newNode;
	newNode = (Node*)malloc(sizeof(Node));
	newNode->data = n;
	if (top1 == NULL)
		newNode->next = NULL;
	else
		newNode->next = top1;
	top1 = newNode;
}

