/*
第1关：程序改错与跟踪调试
任务描述
实验指导书 P139~140 程序改错与跟踪调试题，请按书中的步骤调试程序，找出函数strncate(t,s)和strdelc(s,c)中的错误并改正。

本任务改用在main函数中输入串a、串b以及待删除字符。

输入输出示例
输入：
Programming
Language
a
输出：
ProgrammingLanguage
ProgrmmingLnguge


*/

#include <stdio.h>

void strcate(char[], char[]);
void strdelc(char[], char);

int main(int argc, char const *argv[])
{
    char a[64], b[64], c;
    scanf("%s\n%s\n%c", a, b, &c);
    // printf("%s %s\n", b, a);
    strcate(b, a);
    printf("%s\n", b);
    strdelc(b, 'a');
    printf("%s\n", b);

    return 0;
}

void strcate(char t[], char s[])
{
    int i = 0, j = 0;
    while (t[i])
    {
        i++;
    }
    while ((t[i] = s[j]) != '\0')
    {
        i++;
        j++;
    }
}

void strdelc(char s[], char c)
{
    int j, k;
    for (j = k = 0; s[j] != '\0'; j++)
    {
        if (s[j] != c)
        {
            s[k++] = s[j];
        }
    }
    s[k] = '\0';
}