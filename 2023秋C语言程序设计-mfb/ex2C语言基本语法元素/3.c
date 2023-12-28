#include <stdio.h>

int main(int argc, char const *argv[])
{
    int n, cnt = 0;
    scanf("%d", &n);
    int table[128];
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &table[i]);
    }
    // printf("filled\n");
    for (int i = 0; i < n - 2; i++)
    {
        if ((table[i + 1] > table[i] && table[i + 1] > table[i + 2]) 
        || (table[i + 1] < table[i] && table[i + 1] < table[i + 2]))
        {
            cnt++;
        }
    }
    printf("%d", cnt);

    return 0;
}
