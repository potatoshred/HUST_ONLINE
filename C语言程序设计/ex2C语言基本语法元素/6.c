#include <stdio.h>

void long2ip(unsigned n)
{
    unsigned seg1, seg2, seg3, seg4;
    seg1 = n >> 24;
    seg2 = n << 8 >> 24;
    seg3 = n << 16 >> 24;
    seg4 = n << 24 >> 24;
    printf("%u.%u.%u.%u\n", seg1, seg2, seg3, seg4);
}

int main(int argc, char const *argv[])
{
    unsigned n[128], tmp, cnt = 0;
    for (int i = 0; scanf("%u", &tmp) != EOF; i++)
    {
        n[i] = tmp;
        cnt++;
    }

    for (int i = 0; i < cnt; i++)
    {
        long2ip(n[i]);
    }
    // printf("%d", sizeof(unsigned));
    return 0;
}
