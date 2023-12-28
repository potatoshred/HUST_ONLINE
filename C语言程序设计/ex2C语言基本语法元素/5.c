#include <stdio.h>

int main(int argc, char const *argv[])
{
    unsigned short x, m, n;
    scanf("%hu %hu %hu", &x, &m, &n);
    x >>= m;
    x <<= 16 - n;
    printf("%hx", x);
    return 0;
}
