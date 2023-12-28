#include <stdio.h>
int main()
{
    char c;
    char str[1024];
    int i = 0, cnt = 0;
    while (1)
    {
        c = getchar();
        if (c == EOF)
        {
            str[i] = '\0';
            break;
        }
        else if (c == ' ')
        {
            cnt++;
            if (cnt == 1)
            {
                str[i] = ' ';
            }
            else
            {
                i--;
            }
        }
        else
        {
            cnt = 0;
            str[i] = c;
        }
        i++;
    }
    i = 0;

    while (str[i])
    {
        putchar(str[i++]);
    }
    return 0;
}