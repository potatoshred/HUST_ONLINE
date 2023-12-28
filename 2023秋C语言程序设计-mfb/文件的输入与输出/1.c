/*
任务描述
本关任务：编写程序，设置指令type_c与type_c /p来获取.c文件中的内容，获取type_c+文件名指令时，显示文件中的C语言程序，并为每一行开头加上行号（行号从1开始标注）；获取type_c /p+文件名指令时，为每一行开头加上行号的同时，每10行显示一屏，再次获取字母q，则显示下一屏。（为简化程序，本次测试使用测试文件超过10行，且不用考虑文件格式错误）

文件路径为：src/step1_1/test1.c。

相关知识（略）
编程要求
在右侧编辑器中编写代码，按照任务描述中的要求完成任务。

测试说明
平台会对你编写的代码进行测试，比对你输出的数值与实际正确数值，只有所有数据全部计算正确才能通过测试，以下是对程序的检查的测试说明：

测试输入：
type_c test1.c
预期输出：
文件test1.c的内容及行号

测试输入：

type_c /p test1.c
q
q
预期输出：
文件test1.c的内容分屏显示

注意：此处的输出，分屏后，行号从1重新标注。

测试输入：
type test1.c
预期输出：
指令错误
*/

#include <stdio.h>
#include <string.h>
int main()
{
	// 请在此处编辑您的代码
	/********** Begin **********/
	char cmd1[32], cmd2[32], path[32];
	int flag = 0;
	scanf("%s %s", cmd1, cmd2);
	if (strcmp("type_c", cmd1))
	{
		printf("指令错误");
		return 0;
	}

	if (strcmp("/p", cmd2) == 0)
	{
		flag = 1;
		scanf("%s", path);
	}
	else
	{
		strcpy(path, cmd2);
	}

	FILE *fp;
	fp = fopen("src/step1_1/test1.c", "r");
	if (fp == NULL)
	{
		return 0;
	}
	for (int i = 1; 1; i++)
	{
		printf("%d  ", i);

		char c;
		while ((c = fgetc(fp)) != '\n')
		{
			if (c == EOF)
			{
				return 1;
			}

			putchar(c);
		}

		putchar('\n');
		if (flag)
		{
			if (i % 10 == 0)
			{
				while (getchar() != 'q')
				{
					continue;
				}
				i -= 10;
			}
		}
	}

	fclose(fp);

	/********** End **********/
	return 0;
}