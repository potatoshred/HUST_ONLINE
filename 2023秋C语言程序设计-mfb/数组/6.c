#include <stdio.h>

#define SIZE 100

int isPalindrome(char arr[], int len);

int main()
{
	/**** 输入字符串,调用函数isPalindrome判断是否为回文串，然后输出结果 *******/
	/**********  Begin ***********/
	char c, s[SIZE];
	int length = 0;
	while ((c = getchar()) != EOF)
	{
		s[length] = c;
		length++;
	}

	printf("%s", isPalindrome(s, length) ? "Yes" : "No");
	/**********  End  **********/
	return 0;
}

/**** 在下面编写满足任务要求的递归函数isPalindrome，是回文返回1，不是返回0 *******/
/**********  Begin ***********/
int isPalindrome(char arr[], int len)
{
	for (int i = 0, j = len - 1; i <= j; i++, j--)
	{
		// printf("%c %c\n", arr[i], arr[j]);
		if (arr[i] != arr[j])
		{
			return 0;
		}
	}
	return 1;
}
/**********  End  **********/
