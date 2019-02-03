#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 24
#define FALSE 0
#define TRUE 1
#define MALLOC(x, y) x=(struct node *)malloc(y)

typedef struct node* nodePointer;
typedef struct node {
	int data;
	nodePointer link;
} Node;

void push(nodePointer* top, int value)
{
	nodePointer y;

	y = (nodePointer)malloc(sizeof(Node));
	y->data = value;
	y->link = *top;
	*top = y;
}

int pop(nodePointer* top)
{
	// 함수 내에서 pop한 node를 free해야함.
	nodePointer y;
	int data;

	if(top==NULL)
	{
		return -1;
	}

	else
	{
		data = (*top)->data;
		y = *top;

		*top = (*top)->link;
		//		free(y);
		return data;
	}
}

void main(void)
{
	short int out[MAX_SIZE];
	nodePointer seq[MAX_SIZE];
	nodePointer x, y, top;
	int i, j, n;
	FILE *fp;

	fp = fopen("input.txt", "r");

	fscanf(fp, "%d", &n);

	for(i = 0; i < n; i++)
	{
		out[i] = TRUE; seq[i] = NULL;
	}


	fscanf(fp, "%d %d", &i, &j);

	while(i >= 0)
	{
		push(&seq[i], j);
		push(&seq[j], i);

		fscanf(fp, "%d %d", &i, &j);
	}

	for(i = 0; i < n; i++)
	{
		if(out[i])
		{
			printf("\nNew class : %5d", i);
			out[i] = FALSE;
			x = seq[i];
			top = NULL;

			for(;;)
			{
				while(x)
				{
					j = x->data;
					if(out[j])
					{
						printf("%5d", j);
						out[j] = FALSE;

						push(&top, x->data);
						pop(&x);
					}

					else
						pop(&x);
				}

				if(!top)
					break;
				x = seq[pop(&top)];

			}
		}
	}
	return;
}