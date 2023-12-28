/*
第10关：消除类游戏
任务描述
实验指导书 P143 程序设计第（6）题
本关任务：消除类游戏是一种益智游戏，其核心规则是将一定的彼此相邻的相同元素配对消除。现给定一个n行m列的棋盘，棋盘中的每一个方格上放着一个棋子，每个棋子都有颜色，编号用1~9表示。当一行或一列上有连续3个或3个以上同色棋子时，这些棋子都被同时消除，对应的方格用0表示，请输出经过消除后的棋盘。例如，给定棋盘为：
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
消除后为：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

示例
输入（输入的前两个数字为棋盘的行数和列数）：
4 5
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
输出（同行每个元素之间以空格分隔）：
4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0

测试输入：
4 5
4 4 3 1 4
3 1 1 1 1
4 3 4 1 2
4 4 2 2 2
—— 预期输出 ——
—— 实际输出 ——

4 4 3 0 4
3 0 0 0 0
4 3 4 0 2
4 4 0 0 0


测试输入：
4 4
4 3 4 4
4 4 1 4
9 6 4 8
1 6 3 8
—— 预期输出 ——
—— 实际输出 ——

4 3 4 4
4 4 1 4
9 6 4 8
1 6 3 8

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

void Print_table(int **table, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        printf("%d", table[i][0]);
        for (int j = 1; j < column; j++)
        {
            printf(" %d", table[i][j]);
        }
        putchar('\n');
    }
}

int **Table_init(int row, int column)
{
    int **table = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        table[i] = (int *)malloc(column * sizeof(int));
    }

    return table;
}

void Table_copy(int **table_source, int **table_destination, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            table_destination[i][j] = table_source[i][j];
        }
    }
}

int main(int argc, char const *argv[])
{
    int row, column;
    scanf("%d %d", &row, &column);
    int **table, **table_x, **table_y;
    table = Table_init(row, column);
    table_x = Table_init(row, column);
    table_y = Table_init(row, column);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            scanf("%d", &(table[i][j]));
        }
    }
    Table_copy(table, table_x, row, column);
    Table_copy(table, table_y, row, column);

    for (int i = 0; i < row; i++)
    {
        int repeat = 0, prev = table_x[i][0];

        int *flags = (int *)malloc(column * sizeof(int));
        for (int k = 0; k < column; k++)
        {
            flags[k] = 0;
        }

        for (int j = 0; j < column; j++)
        {
            if (table_x[i][j] == prev)
            {
                repeat++;
                if (repeat >= 3)
                {
                    for (int k = 0; k < repeat; k++)
                    {
                        flags[j - k] = 1;
                    }
                }
            }
            else
            {
                prev = table_x[i][j];
                repeat = 1;
            }
        }

        for (int j = 0; j < column; j++)
        {
            if (flags[j])
            {
                table_x[i][j] = 0;
            }
        }
        free(flags);
    }
    // Print_table(table_x, row, column);

    for (int i = 0; i < column; i++)
    {
        int repeat = 0, prev = table_y[0][i];

        int *flags = (int *)malloc(row * sizeof(int));
        for (int k = 0; k < row; k++)
        {
            flags[k] = 0;
        }

        for (int j = 0; j < row; j++)
        {
            if (table_y[j][i] == prev)
            {
                repeat++;
                if (repeat >= 3)
                {
                    for (int k = 0; k < repeat; k++)
                    {
                        flags[j - k] = 1;
                    }
                }
            }
            else
            {
                prev = table_y[j][i];
                repeat = 1;
            }
        }

        for (int j = 0; j < row; j++)
        {
            if (flags[j])
            {
                table_y[j][i] = 0;
            }
        }
        free(flags);
    }

    // Print_table(table_y, row, column);

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            if (!(table_x[i][j]&&table_y[i][j]))
            {
                table[i][j] = 0;
            }
            
        }
        
    }
    
    Print_table(table, row, column);
    return 0;
}
