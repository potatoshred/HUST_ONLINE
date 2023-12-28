#include <stdio.h>
#include <math.h>
int is_prime(long n)
{
    long tmp = sqrtl(n);
    for (long i = 2; i <= tmp; i++)
    {
        if (!(n % i))
        {
            return 0;
        }
    }
    return 1;
}

int main()
{
    long n;
    scanf("%ld", &n);
    for (long i = 2; i < n; i++)
    {

        if (is_prime(i))
        {
            long M = 1;
            M <<= i;
            M--;
            if (M > n)
            {
                break;
            }
            if (is_prime(M))
            {
                printf("M(%ld)=%ld\n", i, M);
            }

        }
    }
}