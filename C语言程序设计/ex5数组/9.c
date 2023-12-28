/*
第9关：插入字符串

任务描述
实验指导书 P143 程序设计第（5）题
本关任务：编写函数strnins(t,s,n),其功能是：将串s插入串t串的第n个字符的后面，编写main函数测试strnins函数的正确性。

示例
输入（依次为t、s、n）：
iyou
love
1
输出：
iloveyou

测试输入：
iyou
love
1
—— 预期输出 ——
—— 实际输出 ——

iloveyou


测试输入：
life
wonderful_
0
—— 预期输出 ——
—— 实际输出 ——

wonderful_life

*/
#include <stdio.h>
#include <string.h>

void strnins(char *t, char *s, int n)
{
    int len1 = 0;
    int len2 = 0;
    while (t[len1] != '\0')
    {
        len1++;
    }
    while (s[len2] != '\0')
    {
        len2++;
    }
    int len3 = len1 + len2;
    t[len3] = 0;

    for (int i = n; i < len1; i++)
    {
        t[i + len2] = t[i];
    }

    for (int j = 0; j < len2; j++)
    {
        t[n + j] = s[j];
    }
}
int main(int argc, char const *argv[])
{
    char line1[128];
    char line2[128];
    int index;
    scanf("%s %s %d", line1, line2, &index);
    strnins(line1, line2, index);
    printf("%s", line1);
    return 0;
}
