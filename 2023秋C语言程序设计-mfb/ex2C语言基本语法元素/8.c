
#include <stdio.h>

int get_case_id(char c)
{

    if (c == ' ' || c == '\t')
    {
        return 0;
    }
    if (c == '\n')
    {
        return 1;
    }
    if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
    {
        return 2;
    }
    if (c >= '0' && c <= '9')
    {
        return 3;
    }
    return 4;
}

int main(int argc, char const *argv[])
{
    int cnt_char = 0, cnt_word = 0, cnt_line = 0;
    char c, tmp = -1;

    int cn=0;
    while ((c = getchar()) != EOF)
    {
        int case_id = get_case_id(c);
        switch (case_id)
        {
        case 0:
            break;
        case 1:
            cnt_line++;
            break;
        case 2:
            cnt_char++;
            break;
        case 3:
            break;
        case 4:
            cn++;
            if (cn%3 == 1)
            {
                cnt_char++;
                cnt_word++;
            }
            break;

        default:
            break;
        }

        if ((case_id == 0 || case_id == 1) && tmp == 2)
        {
            // printf("%c %d\n", c, cnt_word);
            cnt_word++;
        }

        tmp = case_id;
    }

    printf("字数 %d\n字符数 %d\n行数 %d", cnt_word, cnt_char, cnt_line);
    return 0;
}
