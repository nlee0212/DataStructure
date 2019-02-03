#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 50

typedef enum { head, entry } tagfield;
typedef struct matrix_node *matrix_pointer;
typedef struct entry_node {
	int row;
	int col;
	int value;
} entry_node;
typedef struct matrix_node {
	matrix_pointer down;
	matrix_pointer right;
	tagfield tag;
	union {
		matrix_pointer next;
		struct entry_node entry;
	} u;
} matrix_node;

matrix_pointer hdnode[MAX_SIZE];

matrix_pointer mread(FILE*); // file 에서 matrix 자료를 읽어 리스트에 저장한다.
void mwrite(matrix_pointer); // 행렬을 적절한 포맷 (2차원 행렬형태)으로 출력한다.
void merase(matrix_pointer*); // NULL parameter 인 경우 적절히 처리.

int main() {

	matrix_pointer a, b;
	FILE *fp_A, *fp_B;

	fp_A = fopen("A.txt", "r");
	fp_B = fopen("B.txt", "r");
	a = mread(fp_A);
	b = mread(fp_B);
	mwrite(a);
	mwrite(b);
	merase(&a);
	merase(&b);
	mwrite(a);
	mwrite(b);

	fclose(fp_A);
	fclose(fp_B);

	return 0;
}

matrix_pointer new_node() {
	matrix_pointer node = (matrix_pointer)malloc(sizeof(matrix_node));
	if(node == NULL) {
		printf("Could not allocate memory.\n");
		exit(-1);
	}
	return node;
}

matrix_pointer mread(FILE* fp) // file 에서 matrix 자료를 읽어 리스트에 저장한다.
{
	int num_rows, num_cols, num_terms=0, num_heads, i, j;
	int row, col, value, current_row;
	matrix_pointer temp, last, node;
	entry_node a[MAX_SIZE];
	int tempval, k=0;

	fscanf(fp, "%d %d", &num_rows, &num_cols);

	for(i=0; i<num_rows; i++)
	{
		for(j=0; j<num_cols; j++)
		{
			fscanf(fp, "%d", &tempval);
			if(tempval!=0)
			{
				a[k].col=j;
				a[k].row=i;
				a[k++].value=tempval;
				num_terms++;
			}
		}
	}
	
	j=0;

	num_heads = (num_cols > num_rows) ? num_cols : num_rows;
	node = new_node(); node->tag = entry;
	node->u.entry.row = num_rows;
	node->u.entry.col = num_cols;

	if(!num_heads) node->right = node;
	else {
		for(i=0; i<num_heads; i++) {
			temp = new_node();
			hdnode[i] = temp; hdnode[i]->tag = head;
			hdnode[i]->right = temp; hdnode[i]->u.next=temp;
		}
		current_row = 0; last = hdnode[0];
		for(i=0; i<num_terms; i++) {
			//scanf(&row, &col, &value);
			row=a[j].row;
			col=a[j].col;
			value=a[j++].value;
			if(row > current_row) {
				last->right = hdnode[current_row];
				current_row = row; last = hdnode[row];
			}
			temp = new_node(); temp->tag = entry;
			temp->u.entry.row = row; temp->u.entry.col = col;
			temp->u.entry.value = value; last->right = temp; last = temp;
			hdnode[col]->u.next->down = temp;
			hdnode[col]->u.next = temp;
		}

		// close last row
		last->right = hdnode[current_row];
		// close all column lists
		for(i=0; i<num_cols; i++)
			hdnode[i]->u.next->down = hdnode[i];
		// link all head nodes together
		for(i=0; i<num_heads-1; i++)
			hdnode[i]->u.next = hdnode[i+1];
		hdnode[num_heads-1]->u.next = node;
		node->right = hdnode[0];
	}
	return node;
}

void mwrite(matrix_pointer node) // 행렬을 적절한 포맷 (2차원 행렬형태)으로 출력한다.
{
	int i, row, col, nextrow, nextcol, maxrow=0, maxcol=0, j, k, l;
	if(node==NULL)
	{
		
		return 0;
	}
	
	matrix_pointer temp, tempnext, head = node->right;

	
	
	for(i=0; i<node->u.entry.row; i++) {
		for(temp = head->right; temp != head;
			temp = temp->right)
		{//printf(temp->u.entry.row, temp->u.entry.col, temp->u.entry.value);
			row=temp->u.entry.row;
			col=temp->u.entry.col;
			if(maxrow<row)
				maxrow=row;
			if(maxcol<col)
				maxcol=col;
		}
		head = head->u.next;
	}

	head=node->right;

	for(j=0; j<maxrow+1; j++)
	{
		temp = head->right;
		row=temp->u.entry.row;
		col=temp->u.entry.col;

		for(k=0; k<maxcol+1; k++)
		{
			if(j==row&&k==col)
			{
				printf("%d ", temp->u.entry.value);
				temp=temp->right;
				row=temp->u.entry.row;
				col=temp->u.entry.col;
			}

			else
			{
				printf("0 ");
			}
		}
		head=head->u.next;
		printf("\n");
	}

}

void merase(matrix_pointer*node) // NULL parameter 인 경우 적절히 처리.
{
	int i, num_heads;
	matrix_pointer x, y, head = (*node)->right;
	for(i=0; i<(*node)->u.entry.row; i++) {
		y = head->right;
		while(y != head) {
			x = y; y = y->right; free(x);
		}
		x = head; head = head->u.next; free(x);
	}
	// free remaining head nodes
	y = head;
	while(y != *node) {
		x = y; y = y->u.next; free(x);
	}
	free(*node); *node = NULL;

}
