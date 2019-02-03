#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main (void)
{
	int num;
	int i, j;
	int min;
	int sun = 1;
	int unum, snum = 0;
	double time;
	int random;
	time_t start = 0, end = 0;

	FILE* data;
	data = fopen ("lab1_10000.data", "r");

	start = clock ();

	fscanf (data, "%d", &num);
	unum = num;

	int* U = (int*)malloc (sizeof (int)*num);
	int* sunseo = (int*)malloc (sizeof (int)*num);
	int* S = (int*)malloc (sizeof (int)*num);

	for (i = 0; i < num; i++)
	{
		fscanf (data, "%d", &U[i]);
	}

	for (i = 0; i < num; i++)
	{
		sun = 1;
		for (j = 0; j < num; j++)
		{
			if (U[i] > U[j])
				sun++;
		}

		sunseo[i] = sun;
	}

	for (i = 0; i < num; i++)
	{
		S[U[i] - 1] = U[i];
	}

	

	printf ("Input: ");

	for (i = 0; i < num; i++)
	{
		printf ("%d", U[i]);
		if (i != num - 1)
			printf (", ");
	}
	printf ("\n");

	printf ("Sorted: ");

	for (i = 0; i < num; i++)
	{
		printf ("%d", S[i]);
		if (i != num - 1)
			printf (", ");
	}
	printf ("\n");

	end = clock ();

	time = (double)(start - end)*(-1) / (CLOCKS_PER_SEC);
	printf ("실행시간: %lf", time);


	getchar ();
	return 0;
}