#include <stdio.h>
#include <string.h>

int globalVar = 6;
int main()
{
    // printf("%d", globalVar);
    /******************************/
    // int k = 4;
    // {
    //     float k = 5;
    //     printf("%d", k);
    // }
    /******************************/
    // int i;

    // for (i = 0; i < 5; i++)
    // {
    //     int i = 10;
    //     printf("%d", i);
    //     i++;
    // }
    /******************************/
    // int true = 666;
    // printf("%d", true);
    /******************************/
    // int func(int a){return 0;};
    // printf("%p", func);
    /******************************/
    // int arr[][3] = {{5,6}, {1}};
    // printf("%s", typeof(arr));
    /******************************/
    // char chr = 128;
    // printf("%d\n", chr);

    /******************************/
    // enum birds {SPARROW, PEACOCK, PARROT} a;
    // printf("%d\n", sizeof(a));
    // a = 6;
    // printf("%d", a);
    /******************************/
    // const int func1() { return 0; }
    // int const func2() { return 0; }
    // func1();
    // func2();
    /******************************/
    // float x;
    // int y;
    // sscanf("7 8", "%f %f", &x, &y);
    // printf("%f, %d", x, y);
    /******************************/
    // int d, a = 1, b = 2;
    // d = a++b;
    // d = a+++b;
    // d = a++++b;
    // d = a+++++b;
    // printf("%d %d %d", d, a, b);
    /******************************/
    // 1 < 2 ? return 1 : return 2;
    /******************************/
    // printf("%d", (int x = 2) != 1);
    /******************************/
    // int x = 0;
    // int f()
    // {
    //     if (x == 0)
    //         return x + 1;
    //     else
    //         return x - 1;
    // }
    // int g()
    // {
    //     return x++;
    // }
    // int i = (f() + g()) | g();
    // // int i = g() | (f() + g());
    // printf("%d", i);
    /******************************/
    // int a=1;
    // printf("%d %d", a, a++);
    /******************************/
    // printf("%d", (char)128);
    /******************************/
    // typedef char[] string1;
    // typedef char *string2;
    // typedef char* string3;
    // string1 a = "HAUIABRBF";
    // string2 b = "HAUIABRBF";
    // string3 c = "HAUIABRBF";
    /******************************/
    // if (sizeof(int) > -1)
    //     {printf("True");}
    // else
    //     {printf("False");}
    /******************************/
    // printf("%llu\n", (unsigned char)-1);
    // printf("%llu\n", (unsigned short)-1);
    // printf("%llu\n", (unsigned int)-1);
    // printf("%llu\n", (unsigned long long)-1);
    /******************************/
    // char *p = "Sanfoundry C-Test";
    // p[0] = 'a';
    // p[1] = 'b';
    // printf("%s", p);
    /******************************/
    // printf("abcd""abcd\n");
    // printf("abcd\0""abcd\n");
    /******************************/
    // printf("%d %d %d %d\n", 3/-2, 3%-2, -3%2, -3%-2);
    // printf("%d", (int)-.5);
    /******************************/
    // int x = 7;
    // printf("%d %d %d\n", x%4, x-x/4*4, x&3);
    // x = -7;
    // printf("%d %d %d", x%4, x-x/4*4, x&3);
    /******************************/
    // if (globalVar)
    // {
    //     printf("%d\n", globalVar);
    //     globalVar--;
    //     main(666);

    // }else{globalVar=6;}
    /******************************/
    // int x = 1;
    // if (*(char *)&x)
    //     printf("Little Endian");//0b00000001 00000000
    // else
    //     printf("Big Endian");//0b00000000 00000001
    /******************************/
    // printf("%d %d %d %f", 5.00, (float)5.00, 99999999.0, 5);
    /******************************/
    // char a = 0xff;
    // short b = 0xff00;
    // int c = 0xff000000;
    // printf("%d %d %d", a==0xff, b == 0xff00, c == 0xff000000);
    /******************************/
    // char c = 6;
    // printf("%u %u", sizeof(c), sizeof(~c));
    /******************************/
    // ungetc('6', stdin);
    // ungetc('7', stdin);
    // putchar(getchar());
    // ungetc('8', stdin);
    // ungetc('9', stdin);
    // putchar(getchar());
    /******************************/
    // // int a[2][3] = {1,2,3,4};
    // int a[2][3] = {{1},{2,3,4}};
    // for (int i = 0; i < 3; i++)
    // {
    //     printf("%d %d\n", a[0][i], a[1][i]);
    // }
    /******************************/
    // printf("%s", "0 %d 0", 6);
    /******************************/
    // // signed char a = 0x70;
    // signed char a = 0x80;
    // int d = a;
    // unsigned c = a;
    // unsigned short b = a;
    // printf("%#x %#x %#x", d, c, b);
    /******************************/
    // short a = 0x8080;
    // unsigned d = a;
    // long long c = a;
    // unsigned long long b = a;
    // printf("%#x %lld %#llx %#llx", d, c, c, b);
    /******************************/
    int num1, num2;
    scanf("%d,|%d", &num1, &num2);
    printf("%d,%d", num1, num2);

    /******************************/
    /******************************/
    /******************************/
    /******************************/
    /******************************/
    /******************************/
}
