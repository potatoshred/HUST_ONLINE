/*
第4关：约瑟夫问题（填空）
任务描述
本关任务：完善实验指导书P142的求解约瑟夫问题的源程序：M个人围成一圈，从第一个人开始一次从1至N报数，每当报数为N时报数人出圈，直到圈中只剩下一个人为止。

本任务改为键盘输入 M 和 N 。

示例
输入（第一个数为M，第二个数为N）：
5 3
输出：(每个数占6位宽，第1行为出圈人编号，第2行为最后留在圈中人的编号)
  3   1   5   2
  4
测试输入：
10
4
--
     4     8     2     7     3    10     9     1     6
     5

*/

#include <stdio.h>
#include <stdlib.h>
// #define M 10
// #define N 3
int main(void)
{
    int M, N;
    scanf("%d %d", &M, &N);
    int *a = (int *)malloc(M * sizeof(int)), *b = (int *)malloc(M * sizeof(int));
    int i, j, k;
    for (i = 0; i < M; i++)
    {
        a[i] = i + 1;
    }

    for (i = M, j = 0; i > 1; i--)
    {
        for (k = 1; k <= N; k++)
        {
            if (++j > i - 1)
            {
                j = 0;
            }
        }
        b[M - i] = j ? a[j - 1] : a[i - 1];
        if (j)
        {
            for (k = --j; k < i; k++)
            {
                a[k] = a[k + 1];
            }
        }
    }
    for (i = 0; i < M - 1; i++)
    {
        printf("%6d", b[i]);
    }
    printf("\n%6d", a[0]);

    free(a);
    free(b);
    return 0;
}