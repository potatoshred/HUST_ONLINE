#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// 请根据step4_main.c中主函数流程
// 使用递归的方法补全此函数
int mystrlen(char *s)
{
	/**********  Begin  **********/
	if (*s)
	{
		return mystrlen(s + 1) + 1;
	}
	else
	{
		return 0;
	}

	/**********  End  **********/
}

// 请根据此主函数流程补全step4_stu.h文件中mystrlen()函数

int main()
{
	char s[100];
	int strlenth = 0;
	scanf("%s", &s);
	strlenth = mystrlen(s);
	printf("%d", strlenth);
	return 0;
}