#include <stdio.h>

int main()
{
    /**********Begin**********/
    char c = getchar();
    // scanf("%c", &c);
    if (c >= '0' && c <= '9')
    {
        putchar(c);
    }
    else if (c >= 'a' & c <= 'f')
    {
        printf("%d", c - 87);
    }
    else if (c >= 'A' & c <= 'F')
    {
        printf("%d", c - 55);
    }

    else
    {
        printf("%d", c);
    }

    /**********End**********/
    return 0;
}