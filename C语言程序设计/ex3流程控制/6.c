#include <stdio.h>
int main()
{
    int n, tmp = 1;
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        tmp *= 10;
    }

    for (int i = tmp / 10; i < tmp; i++)
    {
        if (i == (i * i % tmp))
        {
            printf("%d ", i);
        }
    }
}