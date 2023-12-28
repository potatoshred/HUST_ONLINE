/*

第4关：程序完善和修改替换--函数指针（填空）
任务描述
本关任务：实验教材P179 6.3.2节 2.程序完善和修改替换 第（2）题第①问
通过函数指针和菜单选择来调用库函数实现字符串操作：串复制strcpy、串连接strcat或串分解strtok。请完善该程序
( 函数strtok的实现和使用参见理论课教材例8.19)

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

测试输入：
1
hello
world
2
hello
world
3
aaabcccbddd
b
4
—— 预期输出 ——
—— 实际输出 ——

world
helloworld
aaa
*/

#include <stdio.h>
#include <string.h>

int main(int argc, char const *argv[])
{
    char *(*p)(char *, const char *);
    char a[80], b[80], *result;
    int choice;
    while (1)
    {
        do
        {
            scanf("%d", &choice);
        } while (choice < 1 || choice > 4);

        switch (choice)
        {
        case 1:
            p = strcpy;
            break;
        case 2:
            p = strcat;
            break;
        case 3:
            p = strtok;
            break;
        case 4:
            goto down;
            break;
        default:
            continue;
            break;
        }
        getchar();
        scanf("%[^\n]", a);
        getchar();

        scanf("%[^\n]", b);
        getchar();

        result = p(a, b);
        strcat(result, "\n");
        printf("%s\n", result);
    }
down:
    return 0;
}
