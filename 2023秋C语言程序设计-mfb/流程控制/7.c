#include <stdio.h>
#include <math.h>

int is_square_num(int n)
{
    int root = (int)sqrt(n);
    return root * root == n;
}

int main(int argc, char const *argv[])
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++)
    {
        if (is_square_num(i))
        {
            int root1 = (int)sqrt(i);
            for (int j = root1-1; j > 0 ; j--)
            {
                if ((i - j * j) % 10 == 0)
                {
                    int root2 = (int)sqrt((i - j * j) / 10);
                    if (root2 && is_square_num((i - j * j) / 10))
                    {
                        printf("%d=%d*%d=%d*%d*10+%d*%d\n", i, root1, root1, root2, root2, j, j);
                        break;
                    }
                }
            }
        }
    }

    return 0;
}
