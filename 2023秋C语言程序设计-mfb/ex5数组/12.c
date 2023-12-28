/*
第12关：迷宫问题
任务描述
实验指导书 P144 程序设计第（11）题
本关任务：迷宫问题。编程找出从入口（左上角方格）经过迷宫到达出口（右下角方格）的所有路径，迷宫问题示意如下方数字阵列所示，0所表示的地方是不可以通行的，只能从1走到与它相邻（四邻域：上、下、左、右相邻）的1上，且不能走重复路径。
迷宫问题示意图：
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1

本任务由键盘输入迷宫的行数和列数，以及迷宫的图案。

示例
输入：(前两位数字分别为迷宫的行数和列数)
6 10
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
输出（解的编号、路径）：
1
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 1 1 1 0 0 0 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
2
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 1 1 1 0
1 0 0 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1
3
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 1 1 1 1 0
1 0 0 0 0 1 0 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 0 0 0 1 0
0 0 0 0 0 0 0 0 1 1


测试输入：
6 10
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
—— 预期输出 ——
—— 实际输出 ——

1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 1 1 1 0 0 0 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1


测试输入：
6 10
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
—— 预期输出 ——
—— 实际输出 ——

1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 1 1 1 0 0 0 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1


测试输入：
6 10
1 0 0 0 0 0 0 0 0 0
1 0 1 1 0 1 1 1 1 0
1 1 1 0 0 1 1 0 1 0
1 0 0 1 1 1 0 0 1 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
—— 预期输出 ——
—— 实际输出 ——

1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 0 0 0 0 0 0 0
1 0 0 1 1 1 0 0 0 0
1 1 1 1 0 1 1 1 1 0
0 0 0 0 0 0 0 0 1 1
*/

#include <stdio.h>
#include <stdlib.h>
int cnt = 1;

void Print_table(int **table, int row, int column)
{
    for (int i = 0; i < row; i++)
    {
        printf("%d", (table[i][0] == 2));
        for (int j = 1; j < column; j++)
        {
            printf(" %d", (table[i][j] == 2));
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
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            table[i][j] = 0;
        }
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

void DFS(int **checkboard, int **map, int row, int column, int x, int y)
{
    if (x >= 0 && x < row && y >= 0 && y < column && checkboard[x][y] == 1)
    {
        checkboard[x][y] = 2;

        if (x == row - 1 && y == column - 1)
        {
            // putchar('\n');
            printf("%d\n", cnt);
            cnt++;
            Print_table(checkboard, row, column);
            // return;
        }
        else
        {
            DFS(checkboard, map, row, column, x, y + 1);
            DFS(checkboard, map, row, column, x, y - 1);
            DFS(checkboard, map, row, column, x + 1, y);
            DFS(checkboard, map, row, column, x - 1, y);
        }
        checkboard[x][y] = 1;
        // map[x][y] = 7;
    }
}

int main(int argc, char const *argv[])
{
    int row, column;
    scanf("%d %d", &row, &column);
    int **checkboard = Table_init(row, column);
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            scanf("%d", &(checkboard[i][j]));
        }
    }

    int **checkboard_tmp = Table_init(row, column);
    Table_copy(checkboard, checkboard_tmp, row, column);

    int **map = Table_init(row, column);
    map[0][0] = 1;
    map[row - 1][column - 1] = 1;

    DFS(checkboard_tmp, map, row, column, 0, 0);

    putchar('\n');
    // Print_table(checkboard, row, column);
    // putchar('\n');
    // Print_table(map, row, column);
    return 0;
}
