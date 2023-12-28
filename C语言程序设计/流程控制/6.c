#include <stdio.h>

int max_factor(int a, int b)
{
    if (a == b)
    {
        return a;
    }

    int tmp, max, min;
    max = (a > b) ? a : b;
    min = (a > b) ? b : a;
    while (tmp > 0)
    {
        tmp = max - min;
        if (tmp > min)
        {
            max = tmp;
        }
        else if (tmp < min)
        {
            max = min;
            min = tmp;
        }
        else
        {
            return tmp;
        }
    }

    return tmp;
}

int main(int argc, char const *argv[])
{
    int a, b;
    scanf("%d %d", &a, &b);
    int mf = max_factor(a, b);
    printf("%d %d", mf, a/mf*b);

    return 0;
}
