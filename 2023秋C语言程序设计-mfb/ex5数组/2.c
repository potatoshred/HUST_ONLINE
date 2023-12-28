/*
第2关：去掉重复的字符（填空）
任务描述
实验指导书 P140~141 程序完善与修改替换第（1）题
请对书本上去掉重复字符的程序进行完善，将完善之后的程序提交评测。

示例：
输入：
12eerer

输出：
12er

测试输入：
112erf///\\3egyy4iwiiuhdefza1
 预期输出 ——
12erf/\3gy4iwuhdza
*/
#include <stdio.h>
#include <string.h>
void RemoveDuplicate(char *s);
int main()
{
    char str[200];
    // printf("Input strings, end of Ctrl+z\n");
    while (fgets(str, 200, stdin) != NULL)
    {
        RemoveDuplicate(str);
        printf("%s", str);
    }
    return 0;
}

void RemoveDuplicate(char *s)
{
    int r, w, i, len;
    len = strlen(s);
    for (r = w = 0; r < len; r++)
    {
        if (s[r] != '\0')
        {
            s[w++] = s[r];
            for (i = r + 1; i < len; i++)
            {
                if (s[i] == s[r])
                {
                    s[i] = '\0';
                }
            }
        }
    }
    s[w]='\0';
}