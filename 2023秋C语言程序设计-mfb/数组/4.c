#include <stdio.h>

void strnCpy(char t[], char s[], int n)
{
	/**********  Begin  **********/
	int length = 0;
	while (s[length] != '\n')
	{
		length++;
	}
	n = (n > length) ? length : n;
	for (int i = 0; i < n; i++)
	{

		t[i] = s[i];
	}
	t[n] = '\0';
	/**********  End  **********/
}

#define SIZE 100

int main()
{
	/**********  Begin  **********/
	int n;
	char arr[SIZE];
	char out[SIZE];
	scanf("%[^\n]", &arr);
	scanf("%d", &n);
	strnCpy(out, arr, n);
	printf("%s", out);
	/**********  Begin  **********/
	return 0;
}
