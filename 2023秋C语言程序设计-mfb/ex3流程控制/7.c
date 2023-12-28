#include <stdio.h>
int main()
{
    int n, prev_day, next_day, inc = 0, next_inc;
    scanf("%d", &n);
    scanf("%d", &prev_day);
    for (int i = 1; i < n; i++)
    {
        scanf("%d", &next_day);
        next_inc = next_day - prev_day;
        next_inc = (next_inc > 0) ? next_inc : -next_inc;
        prev_day = next_day;
        inc = (inc > next_inc) ? inc : next_inc;
    }
    printf("%d", inc);
}