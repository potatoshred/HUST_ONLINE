/*
第6关：整数的二进制表示
任务描述
实验指导书 P142 程序设计第（1）题
本关任务：输入一个整数，将它在内存中的二进制表示的每一位转换成对应的数字字符并且存放到一个字符数组中，然后输出该整数的二进制表示（32位有符号整数，输出每4位用空格分隔）。

示例
输入：
1
输出：
0000 0000 0000 0000 0000 0000 0000 0001

测试输入：
-1
—— 预期输出 ——
—— 实际输出 ——

1111 1111 1111 1111 1111 1111 1111 1111

测试输入：
123
—— 预期输出 ——
—— 实际输出 ——

0000 0000 0000 0000 0000 0000 0111 1011
*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    unsigned tmp = (unsigned)n;
    unsigned mask = (unsigned)1 << (8 * sizeof(int) - 1);
    for (int i = 0; i < 8 * sizeof(int); i++)
    {

        printf("%d", (tmp & mask) >> (8 * sizeof(int) - 1));
        tmp <<= 1;
        if (i % 4 == 3)
        {
            putchar(' ');
        }
    }

    return 0;
}
