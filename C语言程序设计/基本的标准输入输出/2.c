#include <stdio.h>

int main()
{
    /**********Begin**********/
    unsigned short n;
    scanf("%hu", &n);

    unsigned short a, b, c;
    a = n >> 12;
    b = n << 4;
    b >>= 8;
    b <<= 4;
    c = n << 12;

    printf("%hu", a | b | c);
    /**********End**********/
    return 0;
}