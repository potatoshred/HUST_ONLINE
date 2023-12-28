/*
第7关：完全数

任务描述
实验课本 实验4 程序设计第（2）题
本关任务：设计一个函数，判定形参n是否为完全数，如果是，以n的真因子之和的形式输出结果，否则，输出”n is not a perfect number“。

相关知识
完全数的特点是它的所有真因子(除自身以外的所有因子，包括1)之和恰好等于它本身

编程要求
根据提示，在右侧编辑器补充代码，判断输入的正整数是否是完全数。

测试说明
平台会对你编写的代码进行测试：

测试输入：6
预期输出：6=1+2+3

测试输入：5
预期输出：5 is not a perfect number

提示：

输入的正整数n范围：n<=10^8
输出后不用换行

*/

#include <stdio.h>
// #include <math.h>

void isPerfect(int n)
// 请完成isPerfect函数，判断整数n是否为完全数
{
    /**********   Begin   **********/
    int sum = 1;
    int mid = n / 2;
    int factors[1024] = {1};

    int seek = 1;

    for (int i = 2; i <= mid; i++)
    {
        if (n % i == 0)
        {
            sum += i;
            *(factors + seek) = i;
            seek++;
        }
    }

    if (sum == n)
    {
        printf("%d=1", n);
        int i = 1;
        while (factors[i])
        {
            printf("+%d", factors[i]);
            i++;
        }
    }
    else
    {
        printf("%d is not a perfect number", n);
    }

    /**********    End    **********/
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    isPerfect(n);
    return 0;
}
