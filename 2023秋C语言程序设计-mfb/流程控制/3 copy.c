#include <stdio.h>

int main(int argc, char const *argv[])
{
    double a,b;
    char op;
    scanf("%lf %lf %c", &a,&b,&op);
    if (op=='+')
        printf("%.1f", a+b);

    if (op=='-')
        printf("%.1f", a-b);

    if (op=='*')
        printf("%.1f", a*b);

    if (op=='/')
        printf("%.1f", a/b);

    return 0;
}
