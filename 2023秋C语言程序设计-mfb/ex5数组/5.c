/*
第5关：解约瑟夫问题（改进）

任务描述
实验指导书P142 约瑟夫问题第（2）问
本关任务：改进实验指导书P142的求解约瑟夫问题的源程序，采用标记元素而非压缩数组的方法记录出圈者。

示例
输入（第一个数位为M，第二个数为N）：
5 3
输出：（仅输出最后留在圈中人的编号）
4

+++
200000
4
---
147451
*/

#include <stdio.h>
#include <stdlib.h>

int * Next_cur(int *ring_start, int *cur_p, int size)
{
    int *cur = cur_p;
    while (1)
    {
        cur++;
        if ((cur - ring_start) >= size)
        {
            cur = (cur - ring_start) % size + ring_start;
        }
        if (*cur)
        {
            cur_p = cur;
            return cur_p;
        }
        else
        {
            continue;
        }
    }
}

int main(int argc, char const *argv[])
{
    int m, n;
    scanf("%d %d", &m, &n);
    int *circle = (int *)malloc(m * sizeof(int));
    for (int i = 0; i < m; i++)
    {
        circle[i] = i + 1;
    }

    int cnt_step = 1, cnt_ppl = 0, *cur = circle;
    while (1)
    {
        if (cnt_ppl == m - 1)
        {
            break;
        }

        if (cnt_step != n)
        {
            cnt_step++;
            cur = Next_cur(circle, cur, m);
        }
        else
        {

            // printf("%6d", *cur);
            *cur = 0;
            cnt_ppl++;
            cnt_step = 0;
        }
    }
    for (int i = 0; i < m; i++)
    {
        if (circle[i])
        {
            // printf("\n%6d", circle[i]);
            printf("%d", circle[i]);
        }
        
    }
    
    return 0;
}
