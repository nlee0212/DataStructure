#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

typedef struct threadedTree * threadedPointer;
typedef struct threadedTree
{
	short int leftThread;
	threadedPointer leftChild;
	char data;
	threadedPointer rightChild;
	short int rightThread;
} threadedTree;

threadedPointer head;
threadedPointer find;
int findflag = 0;

threadedPointer insucc(threadedPointer tree);
void tinorder(threadedPointer tree);
void tpreorder(threadedPointer tree);
void tpostorder(threadedPointer tree);
void insertRight(char target1, threadedPointer target2);
void insertLeft(char target1, threadedPointer target2);
void printall(void);
threadedPointer getNewNode(char data);
void menu(void);

int main(void)
{
	menu();
	return 0;
}

void findata(threadedPointer head, char target)			// find target data in input threaded tree.
{
	threadedPointer temp;
	if(head != NULL)									// if tree is not empty
	{
		if(head->leftThread == FALSE)					// until reach the left leaf end of the tree.
			findata(head->leftChild, target);			// recursively call the leftChild findata function.
		if(head->data == target)						// if target data found,
		{
			find = head;								// find pointer points to the target node.
			findflag = 1;								// set the findflag = 1.
		}
		if(head->rightThread == FALSE)					// until reach the right leaf end of the tree.
			findata(head->rightChild, target);			// recursively call the rightChild findata function.
	}

}

threadedPointer insucc(threadedPointer tree)
{	// find the inorder successor of tree in a threaded binary tree
	threadedPointer temp;
	temp = tree->rightChild;
	if(tree->rightThread == FALSE)				// if the node is not a right end leaf node.
		while(temp->leftThread == FALSE)		//  until reach the left end leaf node.
			temp = temp->leftChild;				// temp points to leftchild.
	return temp;
}
void tinorder(threadedPointer target)			// Iteratively print the data inorder. 
{
	threadedPointer temp = target;
	for(;;)
	{
		temp = insucc(temp);
		if(temp == target) break;
		printf("%3c", temp->data);
	}
}

void tpreorder(threadedPointer target)			// Recursively print the data preorder.
{
	threadedPointer temp = target;
	if(temp)
	{
		if(temp->leftThread == FALSE)
		{
			tpreorder(temp->leftChild);
		}
		if(temp->rightThread == FALSE)
		{
			tpreorder(temp->rightChild);
		}
	}
}

void insertRight(char target1, threadedPointer target2)
{
	threadedPointer parent, child, temp;
	temp = head;
	findata(temp, target1);								// find target1 data.
	if(findflag == 0)									// if not found,
	{
		printf("%c doen't exist! Retry..\n", target1);	// just exit the function and get another command.
		return;
	}
	else												// if found, initialize the findflag.
		findflag = 0;
	parent = find;										// parent  == find (target1)

														// 이 밑에 필요한 부분을 채워주세요.
	child = target2;
	child->rightChild = parent->rightChild;
	child->rightThread = parent->rightThread;
	child->leftChild = parent;
	child->leftThread = TRUE;
	parent->rightChild = child;
	parent->rightThread = FALSE;
	if(!child->rightThread)
	{
		temp = insucc(child);
		temp->leftChild = child;
		temp->leftThread = TRUE;
	}
}
void insertLeft(char target1, threadedPointer target2)
{
	threadedPointer parent, child, temp;
	temp = head;
	findata(temp, target1);									// find target1 data.
	if(findflag == 0)										// if not found,
	{
		printf("%c doen't exist! Retry..\n", target1);		// just exit the function and get another command.
		return;
	}
	else
		findflag = 0;										// if found, initialize the findflag.
	parent = find;											// parent  == find (target1)
															
	child = target2;
	child->leftChild = parent->leftChild;
	child->leftThread = parent->leftThread;
	child->rightChild = parent;
	child->rightThread = TRUE;
	parent->leftChild = child;
	parent->leftThread = FALSE;
	if(!child->leftThread)
	{
		temp = child->leftChild;
		while(!temp->rightThread)
		{
			temp = temp->rightChild;
		}
		temp->rightChild = insucc(temp);
		temp->rightThread = TRUE;
	}
}
threadedPointer getNewNode(char data)
{
	threadedPointer temp;
	temp = (threadedPointer)malloc(sizeof(threadedTree));
	temp->leftChild = temp->rightChild = NULL;
	temp->rightThread = FALSE;
	temp->leftThread = TRUE;
	temp->data = data;
	return temp;
}

void printall(void)
{
	threadedPointer temp = head;
	temp = temp->leftChild;
	tpreorder(temp);				// print preorder.
	temp = head; head->rightChild = head;
	printf("inorder : ");
	tinorder(temp);					// print inorder.
	printf("\n");
}

void menu(void)
{
	FILE* fp = NULL;
	char buffer[10], *parent, *child;
	int  command;
	head = (threadedPointer)malloc(sizeof(threadedTree));	// initialize the root of tree.
	head->data = '-'; head->leftChild = NULL; head->rightChild = NULL; head->leftThread = TRUE; head->rightThread = FALSE;
	fp = fopen("input.txt", "r");
	while(1)
	{
		fgets(buffer, sizeof(buffer), fp);			// get a string.
		command = atoi(strtok(buffer, " "));		// command = 0 or 1 or 2 each respectively implies insert left, insert right, end the process and print. 
		parent = strtok(NULL, " ");
		child = strtok(NULL, " ");
		if(command == 0)							// insert left child
		{
			insertLeft(*parent, getNewNode(*child));
		}
		else if(command == 1)						// insert right child
		{
			insertRight(*parent, getNewNode(*child));
		}
		else if(command == 2)						// end the input, then print the output.
		{
			printall();
			break;
		}
		else continue;
	}
	fclose(fp);
}

/* 제한 사항 : 전역변수 사용가능
주어진 자료구조체 사용
일반 입출력

추가 사항 : preorder(리컬시브 사용가능), inorder(리컬시브 사용 불가), postorder(리컬시브 사용가능) 순서대로 출력

메인함수 내용 변경
root는 '-' 입력으로 고정
insertLeft('알파벳' ,getNewNode('알파벳'))
insertRight('알파벳',getNewNode('알파벳'))
없는 Node 일 경우 에러 반환 후 계속 진행
'2' 가 들어올 경우 종료 후 출력
이미 왼쪽, 오른쪽 자식이 생성된 노드의 경우 추가입력 X
*/