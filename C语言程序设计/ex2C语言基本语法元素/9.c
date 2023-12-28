#include <stdio.h>

char encrypt(char c)
{
    unsigned char seg0, seg1, seg2;
    seg0 = c & 0x3f;                            // 0b 0011 1111
    seg1 = seg0 & 0x15;                         // 0b 0001 0101
    seg2 = seg0 & 0x2a;                         // 0b 0010 1010
    c = (seg1 << 1) | (seg2 >> 1) | (c & 0xc0); // 0b 1100 0000

    seg1 = c & 0xc0; // 0b 1100 0000
    seg2 = c & 0x3f; // 0b 0011 1111

    char offset = seg1 >> 6;

    seg2 = (seg2 << offset) & 0x3f | (seg2 >> (6 - offset));

    return seg1 | seg2;
}

int main(int argc, char const *argv[])
{
    char c;
    while ((c = getchar()) != EOF)
    {
        c = encrypt(c);
        putchar(c);
    }

    return 0;
}
