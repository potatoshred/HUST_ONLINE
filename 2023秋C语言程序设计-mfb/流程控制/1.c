#include <stdio.h>

int main(int argc, char const *argv[])
{
    int a, b, c;
    scanf("%d %d %d", &a, &b, &c);
    if ((c > a && c < b) || (c > b && c < a))
    {
        printf("C %d", c);
    }
    else if ((b >= c && b < a) || (b <= c && b > a))
    {
        printf("B %d", b);
    }
    else
    {
        printf("A %d", a);
    }

    return 0;
}
