#include <stdio.h>
#define PI 3.14159
int main()
{
    int f;
    short p, k;
    double c, r, s;
    scanf("%d %lf", &f, &r);

    /*任务1*/
    printf("Input Fahrenheit:");
    c = 5.0 / 9 * (f - 32);
    printf("\n %d(F)=%.2f(C)\n\n", f, c);
    /*任务2*/
    printf("input the radius r:");
    s = PI * r * r;
    printf("\nThe acreage is %.2lf\n\n", s);
    /*任务3*/
    k = 0xa1b2, p = 0x8423;
    short newint = (p & 0xff00) | ((unsigned short)k >> 8);
    printf("new int = %#hx\n\n", newint);
    return 0;
}