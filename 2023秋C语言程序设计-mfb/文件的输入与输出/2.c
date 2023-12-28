/*
任务描述
本关任务：编写函数，将三个文件进行复制拼接到一个新文件中。

相关知识（略）
编程要求
编写相应的函数，将三个文件进行复制拼接。

测试说明
平台会对你编写的代码进行测试：

测试结果为三个文件内容拼接即可，文件内容之间用回车分隔。*/

#include <stdio.h>

/*********************************************************************************
  完成函数，连接filename1、filename2 和 filename3 三个文件的内容到 filename 文件中
  先连接file1，再连接file2，最后连接file3
  ********************************************************************************/
void connect(char *filename, char *filename1, char *filename2, char *filename3)
{
    // 请在此处编辑您的代码
    /********** Begin **********/
    char buf[1024];
    FILE *fp0, *fp1, *fp2, *fp3;
    fp0 = fopen(filename, "w");
    fp1 = fopen(filename1, "r");

    while (fgets(buf, sizeof(buf), fp1) != NULL)
    {
        fputs(buf, fp0);
    }
    fp2 = fopen(filename2, "r");
    while (fgets(buf, sizeof(buf), fp2) != NULL)
    {
        fputs(buf, fp0);
    }
    fp3 = fopen(filename3, "r");
    while (fgets(buf, sizeof(buf), fp3) != NULL)
    {
        fputs(buf, fp0);
    }

    fclose(fp0);
    fclose(fp1);
    fclose(fp2);
    fclose(fp3);

    /********** End **********/
}

int main()
{
    /**********  Begin  **********/

    char buf[1024];
    char *file1 = "src/step2_1/test1.c"; // 源文件1
    char *file2 = "src/step2_1/test2.c"; // 源文件2
    char *file3 = "src/step2_1/test3.c"; // 源文件3
    char *file = "src/step2_1/test.c";   // 目标文件
    FILE *fp;                            // 目标文件的指针

    connect(file, file1, file2, file3); // 将源文件file1、file2和file3的内容连接到目标文件file中

    fp = fopen("src/step2_1/test.c", "r");
    while (fgets(buf, sizeof(buf), fp) != NULL) // 读取目标文件
    {
        printf("%s", buf);
    }
    fclose(fp);
    fp = fopen("src/step2_1/test.c", "w");
    fclose(fp);
    /**********   End   **********/
    return 0;
}