/*
第11关：N阶顺转方阵
任务描述
实验指导书 P144 程序设计第（10）题
本关任务：将1、2、3、…、n^2从左上角开始，由外层至中心按顺时针方向螺旋排列所形成的数字方阵，成为n阶顺转方阵，5阶顺转方阵如下方数字阵列所示。编写程序，读入n，构造并输出n阶顺转方阵。
5阶顺转方阵：
1  2  3  4  5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9
输出时不需严格对齐，行中以单个空格分隔、每n个数换行即可：
1 2 3 4 5
16 17 18 19 6
15 24 25 20 7
14 23 22 21 8
13 12 11 10 9

示例
输入：
3
输出：
1 2 3
8 9 4
7 6 5



测试输入：
3
—— 预期输出 ——
—— 实际输出 ——

1 2 3
8 9 4
7 6 5


测试输入：
1
—— 预期输出 ——
—— 实际输出 ——

1
*/

#include <stdio.h>
#include <stdlib.h>

void Print_table(int **table, int dimension)
{
    for (int i = 0; i < dimension; i++)
    {
        printf("%d", table[i][0]);
        for (int j = 1; j < dimension; j++)
        {
            printf(" %d", table[i][j]);
        }
        putchar('\n');
    }
}

int main(int argc, char const *argv[])
{
    int dimension;
    scanf("%d", &dimension);
    int **table = (int **)malloc(dimension * sizeof(int *));
    for (int i = 0; i < dimension; i++)
    {
        table[i] = (int *)malloc(dimension * sizeof(int));
    }

    for (int i = 0; i < dimension; i++)
    {
        for (int j = 0; j < dimension; j++)
        {
            table[i][j] = 0;
        }
    }
    table[0][0] = 1;

    if (dimension % 2)
    {
        table[dimension / 2][dimension / 2] = dimension * dimension;
        for (int i = dimension / 2 - 1; i >= 0; i--)
        {
            table[i][i] = table[i + 1][i + 1] - 8 * (dimension / 2 - i);
        }
    }
    else
    {
        for (int i = 1; i < dimension / 2; i++)
        {
            table[i][i] = table[i - 1][i - 1] + 4 * (dimension + 1 - i * 2);
        }
    }

    for (int i = 0; i < dimension / 2; i++)
    {
        for (int j = 0; j < dimension - i * 2; j++)
        {
            table[i][i + j] = table[i][i] + j;
        }
        for (int j = 0; j < dimension - i * 2; j++)
        {
            table[i + j][dimension - 1 - i] = table[i][dimension - 1 - i] + j;
        }
        for (int j = 0; j < dimension - i * 2; j++)
        {
            table[dimension - 1 - i][dimension - 1 - i - j] = table[dimension - 1 - i][dimension - 1 - i] + j;
        }
        for (int j = 0; j < dimension - i * 2 - 1; j++)
        {
            table[dimension - 1 - i - j][i] = table[dimension - 1 - i][i] + j;
        }
    }
    Print_table(table, dimension);
}