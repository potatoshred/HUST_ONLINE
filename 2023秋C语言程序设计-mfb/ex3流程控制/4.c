#include <stdio.h>

int have_child(int x)
{
    int k = x >> 1;
    for (int i = 2; i <= k; i++)
    {
        if (!(x % i))
        {
            return 1;
        }
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    int tmp = 1;
    for (int i = 0; i < n; i++)
    {
        tmp *= 10;
    }

    for (int i = tmp / 10; i < tmp; i++)
    {
        int cnt = 0, ii=i;
        while (ii)
        {
            if (have_child(ii))
            {
                cnt++;
            }
            ii /= 10;
        }
        if (cnt == n)
        {
            printf("%d ", i);
        }
    }
}