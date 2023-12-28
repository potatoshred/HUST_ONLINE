/*
第7关：删除重复元素
任务描述
实验教材P182 程序设计第（2）题

定义函数RemoveSame(a,n)，去掉有n个元素的有序整数序列a中的重复元素，返回去重后序列的长度。

示例
输入：
5
3 3 3 6 6

输出：注意不需要输出结果长度后的内容
3 6
2


测试输入：
6
2 4 4 6 6 7
—— 预期输出 ——
—— 实际输出 ——

2 4 6 7
4

*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[])
{
    int num;
    scanf("%d", &num); // 输入序列的长度

    int *arr_in = malloc(num * sizeof(int)); // 分配内存用于存储输入序列
    for (int i = 0; i < num; i++)
    {
        scanf("%d", arr_in + i); // 逐个输入序列中的元素
    }

    int *arr_out = malloc(num * sizeof(int)); // 分配内存用于存储输出序列
    
    int cur = *arr_in; // 初始化当前元素为第一个输入的元素
    *arr_out = cur; // 将第一个输入的元素放入输出序列
    int cnt = 1; // 初始化计数器为1

    for (int i = 1; i < num; i++)
    {
        if (*(arr_in+i) <= cur) // 如果当前输入元素小于或等于当前元素
        {
            continue; // 跳过当前元素，继续下一个
        }
        else
        {
            *(arr_out+cnt) = cur = *(arr_in+i); // 当前输入元素大于当前元素，将其放入输出序列
            cnt++; // 计数器加一
        }
    }
    
    // 输出去重后的序列
    printf("%d", *arr_out); // 输出第一个元素
    for (int i = 1; i < cnt; i++)
    {
        printf(" %d", *(arr_out+i)); // 逐个输出序列中的元素
    }
    printf("\n%d", cnt); // 输出去重后序列的长度

    free(arr_in); // 释放输入序列内存
    free(arr_out); // 释放输出序列内存
    return 0;
}