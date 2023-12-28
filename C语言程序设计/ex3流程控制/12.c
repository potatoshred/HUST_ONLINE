#include <stdio.h>

void split_num(int n, int *num_list)
{
    for (int i = 0; i < 5; i++)
    {
        num_list[i] = n % 10;
        n /= 10;
    }
}

int is_unique_digit(int n)
{
    int num_list[5];
    split_num(n, num_list);
    int tmp[10] = {0};
    for (int i = 0; i < 5; i++)
    {
        tmp[num_list[i]]++;
        if (tmp[num_list[i]] > 1)
        {
            return 0;
        }
    }

    return 1;
}

int is_complementary(int *num_list, int *num_list2)
{
    int table[10] = {0};
    for (int i = 0; i < 5; i++)
    {
        table[num_list[i]]++;
        table[num_list2[i]]++;
    }
    for (int i = 0; i < 10; i++)
    {
        if (table[i] > 1)
        {
            return 0;
        }
    }

    return 1;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    int num_list[5], num_list2[5];
    for (int i = 1234; i <= 98765; i++)
    {
        if (is_unique_digit(i))
        {
            split_num(i, num_list);
            int another = i / n;
            if (n * another != i)
            {
                continue;
            }

            if (is_unique_digit(another))
            {
                split_num(another, num_list2);
                if (is_complementary(num_list, num_list2))
                {
                    printf("%05d/%05d=%d\n", i, another, n);
                }
            }
        }
    }

    return 0;
}
