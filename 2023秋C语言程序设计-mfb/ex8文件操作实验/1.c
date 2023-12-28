/*
第1关：源程序完善和修改替换2.(1)
任务描述
本关任务：参考实验指导书P225-226页内容，功能要求是，通过命令行参数将指定的文本文件内容显示在屏幕上。给出的源程序中存在一些逻辑错误，对程序进行修改、调试，使之能够正确完成指定任务。

编程要求
根据提示，在右侧编辑器修改代码。

测试说明
平台会对你编写的代码进行测试：

测试输入：
./cat test1.txt
—— 预期输出 ——
—— 实际输出 ——

1234567
abcdefg
!@#$%^&
1234567
abcdefg
!@#$%^&
1234567
abcdefg
!@#$%^&

*/

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
    FILE *fp;
    if (argc != 2)
    {
        printf("Arguments error!\n");
        exit(-1);
    }
    if ((fp = fopen(argv[1], "r")) == NULL)
    { /* fp指向filename */
        printf("Can't open %s file!\n", argv[1]);
        exit(-1);
    }

    int c;
    while ((c = fgetc(fp))!=EOF)
    {
        putchar(c);

    }           /* 向显示器中写从filename中读取的字符 */

    fclose(fp); /* 关闭filename */
    return 0;
}
