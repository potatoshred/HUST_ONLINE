/*
第3关：去掉重复字符（改进）
任务描述
实验指导书 P140~141 程序完善与修改替换第（1）题
请通过空间换时间的方法对第2关去掉重复字符的程序进行改进，使算法的时间复杂度由O(n^2)降低为O(n)。

示例：
输入：
12eerer

输出：
12er


*/
#include <stdio.h>

int main(int argc, char const *argv[])
{
    char line[1024];
    scanf("%s", line);
    char table[128] = {0};

    char *tmp = line;
    while (*tmp!='\0')
    {
        table[*tmp]+= 1;
        if (table[*tmp]==1)
        {
            putchar(*tmp);
        }
        tmp++;
    }
    
    return 0;
}
