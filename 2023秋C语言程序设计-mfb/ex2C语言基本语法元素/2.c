#include <stdio.h>

int main(int argc, char const *argv[])
{
    long long n;
    scanf("%lld", &n);
    printf("%lld是", n);
    if (!n)
    {
        printf("1位数，且各位数字之和为0。");
    }
    
    int cnt = 0;
    long long sum = 0;
    while (n)
    {
        sum += n % 10;
        n /= 10;
        cnt++;
    }
    printf("%d位数，且各位数字之和为%lld。", cnt, sum);
    return 0;
}
