#include <stdio.h>
#include <string.h>
#define MAX_VERTICES 30
#define MIN2(x,y) ((x) < (y) ? (x) : (y))
short int dfn[MAX_VERTICES];
short int low[MAX_VERTICES];
int n = 0; /* vertices currently in use */
#define FALSE 0
#define TRUE 1
short int visited[MAX_VERTICES];
int num;
void init();
void bicon(int, int);
void append(struct node** head_ref, int new_data);
typedef struct node *node_pointer;
typedef struct node {
	int vertex;
	node_pointer link;
}node;
node_pointer graph[MAX_VERTICES];
typedef struct edge *edge_pointer;
typedef struct edge {
	int first;
	int second;
	edge_pointer link;
}edge;
edge* head;
void push(int , int );
void pop(int*, int*);

void main()
{
	FILE*fp = fopen("input.txt", "r");
	int i,j;
	int v;
	char temp;
	head = (edge*)malloc(sizeof(edge));
	
	fscanf(fp, "%d", &n);
	fscanf(fp, "%c", &temp);

	for (i = 0;i < n;i++)
	{
		node_pointer w = malloc(sizeof(node));
		w->link = NULL;
		node_pointer ptemp;
		graph[i] = (node_pointer)malloc(sizeof(node));
		graph[i] = NULL;
		char*string = (char*)malloc(sizeof(char)*100);
		fgets(string, 100, fp);
		v = string[0]-48;
		for (j = 1;;j++)
		{
			if (string[j] == '\n')
				break;
			else if (string[j]-48 <= n && string[j]-48 >= 0)
			{
				append(&graph[i], string[j] - 48);
			}
			else if (string[j] != ' ')
				break;
		}
		
	}


	init();
	bicon(3, -1);
}

void append(struct node** head_ref, int new_data)
{
	/* 1. allocate node */
	struct node* new_node = (struct node*) malloc(sizeof(struct node));

	struct node *last = *head_ref;  /* used in step 5*/

									/* 2. put in the data  */
	new_node->vertex = new_data;

	/* 3. This new node is going to be the last node, so make next
	of it as NULL*/
	new_node->link = NULL;

	/* 4. If the Linked List is empty, then make the new node as head */
	if (*head_ref == NULL)
	{
		*head_ref = new_node;
		return;
	}

	/* 5. Else traverse till the last node */
	while (last->link != NULL)
		last = last->link;

	/* 6. Change the next of last node */
	last->link = new_node;
}


void init(void)
{
	int i;
	for (i = 0; i < n; i++) {
		visited[i] = FALSE;
		dfn[i] = low[i] = -1;
	}
	num = 0;
}

void bicon(int u, int v)
{
	node_pointer ptr;
	int w, x, y;
	dfn[u] = low[u] = num++;
	for (ptr = graph[u];ptr;ptr = ptr->link)
	{
		w = ptr->vertex;
		if (v != w && dfn[w] < dfn[u])
			push(u, w);/*add edge to stack*/
		if (dfn[w] < 0)
		{/*w has not been visited*/
			bicon(w, u);
			low[u] = MIN2(low[u], low[w]);
			if (low[w] >= dfn[u])
			{
				printf("New biconnected component: ");
				do { /* delete edge from stack */
					pop(&x, &y);
					printf("<%d,%d> ", x, y);
				} while (!((x == u) && (y == w)));
				printf("\n");
			}
		}
		else if (w != v) low[u] = MIN2(low[u], dfn[w]);
	}
}

void push(int fst, int sec)
{
	edge* ptr = (edge*)malloc(sizeof(edge));

	ptr->first = fst;
	ptr->second = sec;
	ptr->link = head;
	head = ptr;
	
}

void pop(int* fst, int*sec)
{
	edge* ptr = (edge*)malloc(sizeof(edge));
	ptr = head;
	head = head->link;
	*fst = ptr->first;
	*sec = ptr->second;
	//free(ptr);
}