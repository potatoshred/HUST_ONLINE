#include <stdio.h>

int main(int argc, char const *argv[])
{
    double a,b;
    char op;
    scanf("%lf %lf %c", &a,&b,&op);
    switch (op)
    {
    case '+':
        printf("%.1f", a+b);
        break;
    case '-':
        printf("%.1f", a-b);
        break;
    case '*':
        printf("%.1f", a*b);
        break;
    case '/':
        printf("%.1f", a/b);
        break;
    default:
        break;
    }
    return 0;
}
