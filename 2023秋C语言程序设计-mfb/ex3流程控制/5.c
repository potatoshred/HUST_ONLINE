#include <stdio.h>
int main()
{
    int income, tax;
    scanf("%d", &income);
    if (income < 1000)
    {
        tax = 0;
    }
    else if (income < 2000)
    {
        tax = 0 + (income - 1000) * 0.05;
    }
    else if (income < 3000)
    {
        tax = 50 + (income - 2000) * 0.1;
    }
    else if (income < 4000)
    {
        tax = 150 + (income - 3000) * 0.15;
    }
    else if (income < 5000)
    {
        tax = 300 + (income - 4000) * 0.2;
    }
    else
    {
        tax = 500 + (income - 5000) * 0.25;
    }
    printf("%d", tax);
}