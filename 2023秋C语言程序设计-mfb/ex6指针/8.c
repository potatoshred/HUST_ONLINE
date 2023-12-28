/*
第8关：旋转图像
任务描述
实验指导书P182 程序设计第（4）题

输入图像矩阵的行数n和列数m，接下来的n行每行输入m个整数，表示输入的图像，输出原始矩阵逆时针旋转90°后的矩阵。

输入输出示例
输入：
2 3
1 5 3
3 2 4

输出：
3 4
5 2
1 3


*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int row, column;
    scanf("%d %d", &row, &column);

    int **matrix = (int **)malloc(row * sizeof(int *));
    for (int i = 0; i < row; i++)
    {
        matrix[i] = (int *)malloc(column * sizeof(int));
    }
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < column; j++)
        {
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int j = 0; j < column; j++)
    {
        printf("%d", matrix[0][column - j - 1]);
        for (int i = 1; i < row; i++)
        {
            printf(" %d", matrix[i][column - j - 1]);
        }
        putchar('\n');
    }

    for (int i = 0; i < row; i++)
    {
        free(matrix[i]);
    }
    free(matrix);
    return 0;
}
