/*
第10关：删除子串
任务描述
实验指导书P183 程序设计第（8）题

本关任务：删除子串。

输入输出示例
示例1：
输入：先输入字符串str,再输入字符串substr。
hello world!
ll

输出：输出删除子串后的结果字符串以及返回值。
heo world!
1

示例2：
输入：
hello world!
how

输出：
hello world!
0


测试输入：
stay hungry stay foolish
stay
—— 预期输出 ——
—— 实际输出 ——

 hungry  foolish
1


测试输入：
Talk is cheap,show me the code.
abcd
—— 预期输出 ——
—— 实际输出 ——

Talk is cheap,show me the code.
0
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char sentence[1024], sep[1024];
    scanf("%[^\n]\n%[^\n]", sentence, sep);
    int cnt = 0;
    char *start_prev;
    char *start = strstr(sentence, sep);
    char tmp[1024];
    if (start != NULL)
    {
        cnt++;
        strncpy(tmp, sentence, start - sentence);
        tmp[start - sentence] = '\0';
        printf("%s", tmp);
        start_prev = start;
        start = strstr(start + strlen(sep), sep);
    }
    else
    {
        printf("%s\n0", sentence);
        return 0;
    }

    while (start != NULL)
    {
        cnt++;
        strncpy(tmp, start_prev + strlen(sep), start - start_prev - strlen(sep));
        tmp[start - start_prev - strlen(sep)] = '\0';
        printf("%s", tmp);
        start_prev = start;
        start = strstr(start + strlen(sep), sep);
    }
    printf("%s", start_prev + strlen(sep));
    printf("\n1");

    return 0;
}
