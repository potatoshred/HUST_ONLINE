/*
第11关：非负整数积
任务描述
实验指导书P183 程序设计第（10）题

本关任务：求两个不超过200位的非负整数积。
（本题涉及高精度计算，可参考理论课教材例8.9 和 实验课教材 例6.17）

输入输出示例
示例一
输入：
123
456

输出：
56088

示例二
输入：
666666666666666666666666666666666666666666666666666666666666666666
22222222222222222222222222222222222222222222222222222222222222222

输出：
14814814814814814814814814814814814814814814814814814814814814814651851851851851851851851851851851851851851851851851851851851851852
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define Length 201

int main(int argc, char const *argv[])
{
    char s1[Length], s2[Length];
    scanf("%s\n%s", s1, s2);
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    int facotr1[Length] = {0}, facotr2[Length] = {0};
    char c;
    for (int i = 0; i < len1; i++)
    {
        facotr1[i] = s1[len1 - 1 - i] - '0';
    }
    for (int i = 0; i < len2; i++)
    {
        facotr2[i] = s2[len2 - 1 - i] - '0';
    }

    int grid[Length][Length * 2] = {{0}};
    for (int i = 0; i < len1; i++)
    {
        for (int j = 0; j < len2; j++)
        {
            grid[i][j + i] += facotr1[i] * facotr2[j] % 10;
            grid[i][j + i + 1] += (facotr1[i] * facotr2[j]) / 10;
        }
    }

    int result[Length * 2] = {0};

    for (int i = 0; i < Length * 2 - 1; i++)
    {
        for (int j = 0; j < Length; j++)
        {
            result[i] += grid[j][i];
        }
        result[i + 1] += result[i] / 10;
        result[i] %= 10;
    }

    int vacant = Length * 2 - 1;
    while (result[vacant] == 0)
    {
        vacant--;
    }
    
    for (int i = vacant; i >= 0; i--)
    {
        printf("%d", result[i]);
    }

    
    return 0;
}
