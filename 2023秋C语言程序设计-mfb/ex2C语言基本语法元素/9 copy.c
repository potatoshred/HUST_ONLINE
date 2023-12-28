#include <stdio.h>
#include <string.h>
int main()
{
    char ch[900];
    scanf("%s", ch);
    int l = strlen(ch);
    for (int i = 0; i < l; i++)
    {
        char a = ch[i];
        char b, c;
        b = (unsigned)(a & 0x2A) >> 1 | ((a & 0x15) << 1);
        c = (unsigned char)a >> 6;
        for (int count = 1; count <= c; count++)
        {
            b = ((b << 1) & 0x3f) | ((unsigned)(b & 0x20) >> 5);// 0010 0000
        }
        a = (c << 6) | b;
        printf("%c", a);
    }
    return 0;
}