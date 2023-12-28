/*
第1关：表达式求值的程序验证
任务描述
实验教材P205 7.3.2节 1.表达式求值的程序验证

本关任务：计算并验证实验指导书上表达式的值。

编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试，输入为表达式的序号,输出为表达式的结果。输出形式依据表示式的值，如果表达式的值为整型数，输出对应整型数，如果表达式的值为一个字符，输出对应的字符。
测试输入
1    （对序号为1的表达式求值，假定表达式的值为200）
预期输出
200

测试输入
2    （对序号为2的表达式求值，假定表达式的值为字符B）
预期输出
B
*/

#include <stdio.h>

int main()
{

    while (1)
    {
        char u[] = "UVWXYZ", v[] = "xyz";
        struct T
        {
            int x;
            char c;
            char *t;
        } a[] = {{11, 'A', u}, {100, 'B', v}}, *p = a;
        int id;
        scanf("%d", &id);
        switch (id)
        {
        case 1:
            printf("(++p)->x = %d\n", (++p)->x);
            break;
        case 2:
            printf("(p++, p->c) = %c\n", (p++, p->c));
            break;
        case 3:
            printf("(*p++->t, *p->t) = %c\n", (*p++->t, *p->t));
            break;
        case 4:
            printf("*(++p)->t = %c\n", *(++p)->t);
            break;
        case 5:
            printf("*++p->t = %c\n", *++p->t);
            break;
        case 6:
            printf("++ * p->t = %c\n", ++*p->t);
            break;
        default:
            break;
        }
    }

    return 0;
}
