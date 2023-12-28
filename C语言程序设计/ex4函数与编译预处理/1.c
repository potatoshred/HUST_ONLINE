#include <stdio.h>
long long fibonacci[64] = {0};
long fabonacci(int n)
{
    if (n == 1 || n == 2)
        return 1;
    if (!fibonacci[n])
    {
        fibonacci[n] = fabonacci(n - 1) + fabonacci(n - 2);
    }
    return fibonacci[n];
}
int main()
{
    int i, k;
    long sum = 0;
    scanf("%d", &k);
    for (i = 1; i <= k; i++)
    {
        sum += fabonacci(i);
    }
    printf("%lld", sum);
    return 0;
}