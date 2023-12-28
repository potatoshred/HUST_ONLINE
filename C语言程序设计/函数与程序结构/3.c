#include <stdio.h>

// 请根据step3_main.cpp中的主函数流程，补全此函数
int digit(long n, int k)
{
    /**********  Begin  **********/
    if (n==0&&k==1)
    {
        return 0;
    }
    if (n==0&&k>1)
    {
        return -1;
    }
    int tmp = 1;
    if (n<0)
    {
        n=-n;
    }
    
    for (int i = 0; i < k - 1; i++)
    {
        tmp *= 10;
    }
    if (n >= tmp)
    {
        return n / tmp % 10;
    }
    else
    {
        return -1;
    }

    /**********  End  **********/
}
// 请根据此函数补全step3_stu.h文件中digit()函数
int main()
{
    long n;
    int k;
    scanf("%ld%d", &n, &k);
    if (n < 0)
        n = -n;
    printf("%d", digit(n, k));
    return 0;
}