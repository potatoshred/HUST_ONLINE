
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *p; //  该指针指向连接后的字符串

#define SIZE_INPUT 100
#define SIZE 51

int main0(int argc, char *argv[]); // 带参main0函数原型，相当于本地带参main

int main()
{
    char *inputStr[SIZE_INPUT]; // 指向输入行的每个参数
    int n = 0;                  // 存储参数个数

    char bufferStr[SIZE];
    char in;
    int state = 0, i;
    /*******************************************************************
        以下 Begin ... End  之间的代码模拟命令行的输入和参数串的存储
    ***************  Begin  ********************************************/
    do
    {
        in = getchar();
        switch (state)
        {
        case 0: // 当前状态是空格
            if (in != ' ')
            { // 参数串的第1个字符
                i = 0;
                bufferStr[i++] = in;
                state = 1;
            }
            break;
        case 1: // 当前状态是字符
            if (in == ' ' || in == '\n')
            { // 接收到一个参数串，存储该参数
                bufferStr[i++] = '\0';
                inputStr[n] = (char *)malloc(sizeof(char) * i);
                strcpy(inputStr[n++], bufferStr);
                state = 0;
            }
            else
                bufferStr[i++] = in;
            break;
        }
    } while (in != '\n');
    /****************   End *****************************************/

    main0(n, inputStr); //  调用带参main0函数

    printf("%s", p); //  输出连接后的字符串

    for (i = 0; i < n; i++)
    {
        free(inputStr[i]);
    }
}
/******************************************************************
 在下面编写带参 main0 函数，实现字符串的连接，字符串由命令行给出；
 连接之后的新串无冗余地存储到用`malloc`动态分配的空间，并将该空间首地址赋值给外部指针`p`。

 将本地调试通过的 main 改为 main0，可能需要按题目要求作适当修改，
 比如，这里的 main0 只完成连接操作，不需要输出数据。
 ******************************************************************/

extern char *p; // 外部指针的引用性声明，p指向连接后的串

int main0(int argc, char *argv[])
{
    /**********  Begin  **********/
    // char tmp[100];
    int cnt = 0;
    for (int i = 1; i < argc; i++)
    {
        int j = 0;
        while (argv[i][j++])
        {
            cnt++;
        }
    }

    p = (char *)malloc(sizeof(char) * (cnt + 1));
    char *tmp = p;
    for (int i = 1; i < argc; i++)
    {
        int j = 0;
        while (argv[i][j])
        {
            *tmp = argv[i][j++];
            tmp++;
        }
    }
    *tmp = '\0';
    /**********  End  **********/
}