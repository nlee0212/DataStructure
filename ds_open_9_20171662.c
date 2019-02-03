#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_TERMS 100

typedef struct treeNode* treePtr;
typedef struct treeNode {
	treePtr lchild;
	int data;
	treePtr rchild;
}treeNode;

/* You have to implement the functions below */
void inorder(treePtr);
void preorder(treePtr);
void insert(treePtr*, int);
treePtr modifiedSearch(treePtr, int);

int main()
{
	int i, n, A[MAX_TERMS];
	treePtr tree = NULL;

	/* Open a data input file and
	store the size of input into 'n' and then
	store the integers to be inserted into 'A' array */

	FILE* fp = fopen("input.txt", "r");
	fscanf(fp, "%d", &n);

	for (i = 0;i < n;i++)
	{
		fscanf(fp, "%d", &A[i]);
	}

	for (i = 0; i < n; i++)
	{
		insert(&tree, A[i]);
	}

	/* By using 'inorder' and 'preorder',
	check whether tree was constructed correctly or not. */
	printf("inorder: ");
	inorder(tree);
	printf("\npreorder: ");
	preorder(tree);
	printf("\n");

	fclose(fp);

	return 0;
}

void inorder(treePtr ptr)
{
	if (ptr) {
		if (ptr->data < 1 || ptr->data>1000000)
			return;
		inorder(ptr->lchild);
		printf("%d ", ptr->data);
		inorder(ptr->rchild);
	}
}

void preorder(treePtr ptr)
{
	if (ptr) {
		if (ptr->data < 1 || ptr->data>1000000)
			return;
		printf("%d ", ptr->data);
		preorder(ptr->lchild);
		preorder(ptr->rchild);
	}
}

void insert(treePtr*node, int num)
{
	/* If num is in the tree pointed at by node do nothing;
	otherwise add a new node with data = num */
	treePtr ptr, temp = modifiedSearch(*node, num);
	if (temp || !(*node)) {
		/* num is not in the tree */
		ptr = (treePtr)malloc(sizeof(treeNode));
		ptr->data = num;
		ptr->lchild = ptr->rchild = NULL;
		if (*node) /* insert as child of temp */
			if (num < temp->data)
				temp->lchild = ptr;
			else temp->rchild = ptr;
		else *node = ptr;
	}
}

treePtr modifiedSearch(treePtr node, int num)
{
	treePtr temp = node;
	while (node)
	{
		temp = node;
		if (num < node->data)
			node = node->lchild;
		else if (num > node->data)
			node = node->rchild;
		else
			return NULL;
	}
	return temp;
}