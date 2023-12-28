#include <stdio.h>

int main(int argc, char const *argv[])
{
    long long n, cnt = 0, sum = 0;
    for (int i = 0; i < 10; i++)
    {
        scanf("%lld", &n);
        if (n < 0)
        {
            continue;
        }
        else
        {
            cnt++;
            sum += n;
        }
    }

    if (cnt)
    {
        printf("numbers=%lld, average=%.6lf", cnt, sum * 1.0 / cnt);
    }
    else
    {
        printf("numbers=0, average=0.000000");
    }

    return 0;
}
