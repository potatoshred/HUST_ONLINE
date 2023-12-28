/*
第5关：程序完善和修改替换--函数指针数组（改进）
任务描述
本关任务：实验教材P179 6.3.2节 2.程序完善和修改替换 第（2）题第②问
通过函数指针和菜单选择来调用库函数实现字符串操作：串复制strcpy、串连接strcat或串分解strtok。

请使用转移表而不是switch语句重写第4关程序。

输入输出示例
输入：
1
the more you learn,
the more you get.
2
the more you learn,
the more you get.
3
www.educoder.net
.
4

输出：
the more you get.
the more you learn,the more you get.
www


*/

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *(*p[3])(char *, const char *) = {
        strcpy,
        strcat,
        strtok};
    char a[80], b[80], *result;
    int choice;
    while (1)
    {
        do
        {
            scanf("%d", &choice);
        } while (choice < 1 || choice > 4);

        if (choice == 4)
        {
            goto down;
        }
        else
        {

            getchar();
            scanf("%[^\n]", a);
            getchar();

            scanf("%[^\n]", b);
            getchar();

            result = p[choice - 1](a, b);
            strcat(result, "\n");
            printf("%s", result);
        }
    }
down:
    return 0;
}
