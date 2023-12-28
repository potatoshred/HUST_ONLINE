/*
第9关：逆波兰表达式
任务描述
实验教材P207 程序设计 第（9）题
本关任务：
利用值栈对逆波兰表达式进行求值。逆波兰表达式从键盘输入，其中的运算符仅包含加、减、乘、除4种运算，表达式中的数都是十进制数，用换行符结束输入。由于逆波兰表达式的长度不限，所以值栈要用后进先出链表实现。

编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：
2  1  +  3  *
预期输出：
9
解释:
该算式转化为常见的中缀算术表达式为：((2 + 1) * 3) = 9
测试输入：
4  13  5  /  +
预期输出：
6
解释: 该算式转化为常见的中缀算术表达式为：(4 + (13 / 5)) = 6


测试输入：
4 13 5 / +
—— 预期输出 ——
—— 实际输出 ——

6

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 定义一个结构体，用于表示数字和操作符
typedef struct TEMP
{
    int num;            // 数字或结果
    struct TEMP *next;  // 指向下一个结点的指针
} TOKEN;

// 将元素压入栈中
void Push(TOKEN **stack, int value)
{
    TOKEN *cur = (TOKEN *)malloc(sizeof(TOKEN));  // 分配内存以存储新元素
    cur->num = value;  // 将值存储到新元素中

    // 如果栈为空，则新元素就是栈顶元素
    if (*stack == NULL)
    {
        cur->next = NULL;  // 栈顶元素的下一个为空
        *stack = cur;      // 更新栈顶指针为新元素
        return;
    }
    else
    {
        cur->next = *stack;  // 新元素的下一个是当前栈顶元素
        *stack = cur;        // 更新栈顶指针为新元素
    }
}

// 弹出栈顶元素
int Pop(TOKEN **stack)
{
    int value = (*stack)->num;  // 获取栈顶元素的值
    *stack = (*stack)->next;    // 更新栈顶指针为下一个元素
    return value;               // 返回弹出的值
}

// 检查是否为数字
int IsNum(char *seg)
{
    if (strlen(seg) == 1)  // 如果长度为1
    {
        if (isdigit(*seg))  // 如果是数字字符
        {
            return 1;  // 返回1表示是数字
        }
        else
        {
            return 0;  // 返回0表示不是数字
        }
    }
    else
    {
        return 1;  // 如果长度不为1，假定是数字
    }
}

int main(int argc, char const *argv[])
{
    TOKEN *stack = NULL;  // 初始化栈为空
    char seg[8], operater;  // 存储输入的字符串和操作符
    int value, product, lvalue, rvalue;  // 存储值和计算结果

    // 逐个读取输入的字符串
    while (scanf("%s", seg) != EOF)
    {
        if (!IsNum(seg))  // 如果不是数字，即为操作符
        {
            rvalue = Pop(&stack);  // 弹出栈顶元素作为右操作数
            lvalue = Pop(&stack);  // 弹出栈顶元素作为左操作数

            switch (*seg)  // 根据操作符进行计算
            {
            case '+':
                product = lvalue + rvalue;
                break;
            case '-':
                product = lvalue - rvalue;
                break;
            case '*':
                product = lvalue * rvalue;
                break;
            case '/':
                product = lvalue / rvalue;
                break;
            default:
                break;
            }

            Push(&stack, product);  // 将计算结果压入栈中
        }
        else  // 如果是数字
        {
            value = atoi(seg);  // 将字符串转换为整数
            Push(&stack, value);  // 将数字压入栈中
        }
    }

    printf("%d", stack->num);  // 打印最终结果
    return 0;
}

