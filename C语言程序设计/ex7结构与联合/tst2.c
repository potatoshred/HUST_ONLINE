#include<stdio.h>

char u[] = "UVWXYZ";
char v[] = "xyz";
struct T {
	int x;
	char c;
	char* t;
};

int main()
{	
	struct T a[] = { {11,'A',u},{100, 'B',v} }, * p = a;
	printf("(++p)->x is %d\n", (++p)->x);

	p = a;
	printf("p++,p->c is %c\n", (p++, p->c));

	p = a;
	printf("*p++->t, *p->t is %c\n", (*p++->t, *p->t));

	p = a;
	printf("*(++p)->t is %c\n", *(++p)->t);

	p = a;
	printf("*++p->t is %c\n", *++p->t);

	p = a;
	// puts(u);
	printf("++*p->t is %c\n", ++ * p->t);	//结果为‘W’ 不知原因

	return 0;
}

