#include <stdio.h>

int main(int argc, char const *argv[])
{
    double e, result = 0;
    scanf("%lf", &e);

    long long n = 1;
    do
    {
        if (n % 2)
        {
            result += 1.0 / (n * 2 - 1);
        }
        else
        {
            result -= 1.0 / (n * 2 - 1);
        }
    } while ((e > 0) && (1.0 / ((n++) * 2 - 1) >= e));
    printf("%.6lf", result * 4);

    return 0;
}
