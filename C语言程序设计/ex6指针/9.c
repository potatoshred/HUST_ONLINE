/*
第9关：命令行实现对N个整数排序
任务描述
实验指导书 P182 程序设计第（6）题

本关任务：命令行实现对N个整数排序。

输入输出示例
输入：执行输入的命令，再按照命令输入N个整数。
sort 5 -d      (这是命令行)
4 3 8 5 1      (这是程序执行后输入的5个待排序数据)

输出：输出排序后的结果。
8 5 4 3 1

./sort  12 -d
4 3 8 5 1 3 6 7 8 9 10 12

注意：要求n个整数的存储无冗余。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Str2Int(const char *s)
{
    int len = strlen(s);
    int o = 0;
    for (int i = 0; i < len; i++)
    {
        o *= 10;
        o += s[i] - '0';
    }
    return o;
}

void sort(int table[], int cnt)
{
    for (int i = 0; i < cnt - 1; i++)
    {
        for (int j = 0; j < cnt - 1 - i; j++)
        {
            if (table[j] > table[j + 1])
            {
                int tmp = table[j];
                table[j] = table[j + 1];
                table[j + 1] = tmp;
            }
        }
    }
}

int main(int argc, char const *argv[])
{
    int cnt = Str2Int(argv[1]);
    int *table = (int *)malloc(cnt * sizeof(int));
    for (int i = 0; i < cnt; i++)
    {
        scanf("%d", &table[i]);
    }
    sort(table, cnt);
    if (argc == 2)
    {
        for (int i = 0; i < cnt; i++)
        {
            printf("%d ", table[i]);
        }
    }
    else if (argc == 3 && !strcmp(argv[2], "-d"))
    {
        for (int i = 0; i < cnt; i++)
        {
            printf("%d ", table[cnt - 1 - i]);
        }
    }
    putchar("\n");
    free(table);
    return 0;
}
