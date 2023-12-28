/*
第6关：歌德巴赫猜想

任务描述
实验课本 实验4 程序设计第（1）题
本关任务：设计一个函数对其形参验证歌德巴赫猜想，并以“n=n1+n2”的形式输出结果。

相关知识
哥德巴赫猜想：一个大于等于4的偶数可以表示成两个素数之和

编程要求
根据提示，在右侧编辑器编写函数，验证哥德巴赫猜想。

测试说明
平台会对你编写的代码进行测试：

测试输入：6
预期输出：6=3+3

测试输入：8
预期输出：8=3+5

提示：

输入的偶数范围为：4<=n<=1000000
如果有多对满足要求的素数，打印差值绝对值最大的一对素数
*/

#include <stdio.h>
#include <math.h>

int is_prime(int n)
{
    int mid = sqrt(n);
    for (int i = 2; i <= mid; i++)
    {
        if (n % i == 0)
        {
            return 0;
        }
    }
    return 1;
}

void goldbach(int n)
// 请完成goldbach函数，将大于等于4的偶数n表示成两个素数的和。
{
    /**********   Begin   **********/
    for (int i = 2; i <= n/2; i++)
    {
        if (is_prime(i)&&is_prime(n-i))
        {
            printf("%d=%d+%d", n, i, n-i);
            return ;
        }
        
    }
    /**********    End    **********/
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    goldbach(n);
    return 0;
}
