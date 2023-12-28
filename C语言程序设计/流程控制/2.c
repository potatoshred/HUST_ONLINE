#include <stdio.h>

int is_leap(int year)
{
    return ((!(year % 4)) && (year % 100)) || (!(year % 400));
}

int main(int argc, char const *argv[])
{
    int table[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int year, month, day, sum = 0;
    scanf("%d %d %d", &year, &month, &day);
    for (int i = 0; i < month - 1; i++)
    {
        sum += table[i];
    }
    sum += day;

    if (is_leap(year) && month > 2)
    {
        sum++;
    }

    printf("%d", sum);
    return 0;
}
