#include <stdio.h>

int main(int argc, char const *argv[])
{
    long long n;
    scanf("%lld", &n);
    printf("%lld��", n);
    if (!n)
    {
        printf("1λ�����Ҹ�λ����֮��Ϊ0��");
    }
    
    int cnt = 0;
    long long sum = 0;
    while (n)
    {
        sum += n % 10;
        n /= 10;
        cnt++;
    }
    printf("%dλ�����Ҹ�λ����֮��Ϊ%lld��", cnt, sum);
    return 0;
}
