/*
第2关：源程序完善和修改替换2.(2)
任务描述
本关任务：修改2.(1)的程序，在显示文本的过程中对每一行加一个行号，同时，设计一个显示控制参数/p，使得每显示5行（一屏）就暂停，当用户按下任何一个键，例如"q"就继续显示下一屏。

编程要求
根据提示，在右侧编辑器修改代码。

测试说明
平台会对你编写的代码进行测试：

测试输入：
./cat test2.txt /p
q
q
—— 预期输出 ——
—— 实际输出 ——

1 I am a student.
2 我是一个学生。
3 I am a student.
4 我是一个学生。
5 I am a student.
6 我是一个学生。
7 I am a student.
8 我是一个学生。
9 I am a student.
10 我是一个学生。
11 I am a student.
12 我是一个学生。
*/
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc != 3)
    {
        printf("Arguments error!\n");
        exit(-1);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    { /* fp指向filename */
        printf("Can't open %s file!\n", argv[1]);
        exit(-1);
    }

    char c, prev_c;
    int cnt_line = 1;
    printf("%d ", cnt_line);
    while (!feof(fp))
    {
        c = fgetc(fp);
        if (c != EOF)
        {
            if (prev_c == '\n')
            {
                if (cnt_line%5==0)
                {
                    while (getchar()!='q');
                }
                
                cnt_line++;
                printf("%d ", cnt_line);
            }
            putchar(c);
        }

        prev_c = c;
    }
    /* 向显示器中写从filename中读取的字符 */
    fclose(fp); /* 关闭filename */
    return 0;
}
