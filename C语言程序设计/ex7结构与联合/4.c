/*
第4关：设计字段结构
任务描述
实验教材P207 程序设计 第（1）题
本关任务：
设计一个字段结构 struct bits, 它将一个 8 位无符号字节从最低位到最高位声明为 8 个字段，依次为 bit0, bit1,..., bit7，且 bit0 优先级最高。同时设计8个函数，第 i 个函数以 biti(i=0, 1, ..., 7)为参数，并且在函数体内输出 biti 的值。将 8 个函数的名字存入一个函数指针数组 p_fun。如果 bit0 为 1, 调用 p_fun[0] 指向的函数。如果 struct bits 中有多位为 1，则根据优先级从高到低顺序依次调用函数指针数组 p_fun 中相应元素指向的函数。
8 个函数中的第 0 个函数可以设计为：

void f0(int b){
    printf("the function %d is called!",b);
}
相关知识
为了完成本关任务，你需要掌握：1.结构体。

编程要求
根据题目要求，在右侧编辑器完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：
32   对应字节二进制为：00100000
预期输出：
the function 5 is called!

测试输入：
111   对应字节二进制为：011001111
预期输出：
the function 0 is called!
the function 1 is called!
the function 2 is called!
the function 3 is called!
the function 5 is called!
the function 6 is called!


测试输入：
123
—— 预期输出 ——
—— 实际输出 ——

the function 0 is called!
the function 1 is called!
the function 3 is called!
the function 4 is called!
the function 5 is called!
the function 6 is called!


测试输入：
255
—— 预期输出 ——
—— 实际输出 ——

the function 0 is called!
the function 1 is called!
the function 2 is called!
the function 3 is called!
the function 4 is called!
the function 5 is called!
the function 6 is called!
the function 7 is called!


测试输入：
0
—— 预期输出 ——
—— 实际输出 ——


*/
#include <stdio.h>
#include <stdlib.h>

// 宏定义 TSK(id)，生成函数 f0 到 f7，用于打印函数被调用的信息
#define TSK(id) void f##id() { printf("the function %s is called!\n", #id); }

// 生成函数 f0 到 f7
TSK(0)
TSK(1)
TSK(2)
TSK(3)
TSK(4)
TSK(5)
TSK(6)
TSK(7)

// 定义包含八个位字段的结构体 Bits，用于表示一个字节的每个比特位
struct Bits
{
    unsigned char b0 : 1;
    unsigned char b1 : 1;
    unsigned char b2 : 1;
    unsigned char b3 : 1;
    unsigned char b4 : 1;
    unsigned char b5 : 1;
    unsigned char b6 : 1;
    unsigned char b7 : 1;
};

// 定义联合体 BITS，包含了一个无符号字符和一个 Bits 结构体，用于处理字节的位操作
typedef union
{
    unsigned char x;
    struct Bits octo;
} BITS;

int main(int argc, char const *argv[])
{
    // 定义函数指针数组 p[]，存储函数 f0 到 f7 的指针
    void (*p[])() = {f0, f1, f2, f3, f4, f5, f6, f7};

    // 用于存储输入的整数，表示字节的不同比特位状态
    int cmd_code;

    // 从标准输入读取一个整数，存储在 cmd_code 中
    scanf("%d", &cmd_code);

    // 将输入的整数存储在 BITS 类型的变量 bits 中
    BITS bits = {cmd_code};

    // 根据 bits 中每个比特位的值，选择调用 p[] 中相应索引位置的函数
    if (bits.octo.b0) p[0]();
    if (bits.octo.b1) p[1]();
    if (bits.octo.b2) p[2]();
    if (bits.octo.b3) p[3]();
    if (bits.octo.b4) p[4]();
    if (bits.octo.b5) p[5]();
    if (bits.octo.b6) p[6]();
    if (bits.octo.b7) p[7]();

    // 程序执行完毕，返回 0
    return 0;
}
