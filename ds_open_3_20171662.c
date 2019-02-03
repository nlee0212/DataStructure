#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define max_string_size 100
#define max_pattern_size 100

int failure[max_pattern_size];
char string[max_string_size];
char pat[max_pattern_size];

int main(void)
{
	FILE *fp = fopen("kmp.txt", "r");
	fgets(string, sizeof(string), fp);
	fgets(pat, sizeof(pat), fp);

	fail(pat);//길이알아냄, failure작성 완료

	printf("%d\n", pmatch(string, pat));

	fclose(fp);

	return 0;
}

void fail(char *pat)//길이를알아낸다
{
	int i, j;
	int n = strlen(pat);
	failure[0] = -1;//초기화 (첫번째자리는 비교x)

	for(j = 1; j < n; j++)
	{
		i = failure[j - 1];
		while((pat[j] != pat[i + 1]) && (i >= 0))
			i = failure[i];
		if(pat[j] == pat[i + 1])
			failure[j] = i + 1;
		else failure[j] = -1;
	}
}

int pmatch(char * string, char *pat)
{
	int i = 0, j = 0;
	int lens = strlen(string);
	int lenp = strlen(pat);

	while(i < lens && j < lenp) 
	{
		if(string[i] == pat[j])
		{
			i++;
			j++;
		}
		else if(j == 0) i++; 
		else j = failure[j - 1] + 1;
	}

	return ((j == lenp) ? (i - lenp) : -1);
}

