#include <stdio.h>

int main(int argc, char const *argv[])
{
    long long n, a = 1, b = 1, tmp;
    scanf("%lld", &n);
    printf("%10lld%10lld", a, b);

    for (int i = 2; i < n; i++)
    {

        if (!(i % 8))
        {
            printf("\n");
        }
        printf("%10lld", a + b);
        tmp = a;
        a = b;
        b += tmp;
    }

    return 0;
}
