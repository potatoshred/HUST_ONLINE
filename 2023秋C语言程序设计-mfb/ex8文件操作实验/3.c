/*
第3关：字符串替换3.(1)
任务描述
本关任务：编写一个程序replace，采用命令行的方式，用给定的字符串替换指定文件中的目标字符串，替换后保存在out.txt中。
  你不需要输出out.txt中的内容，由平台输出。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，并输出out.txt中的内容：

测试输入：
./replace test1.txt you they
—— 预期输出 ——
—— 实际输出 ——

So they think we ought to wait here?
I will run they in if the bus isn't going into the town because of the snow today.
In a pinch, they could get home on foot.
they don't know the facts, so keep theyr mouth shut!
We have many patterns in stock for they to choose from.


测试输入：
./replace test2.txt day 123
—— 预期输出 ——
—— 实际输出 ——

What will you do on Sun123?
Are you free to123?
What did you do for the past few 123s?
To123 is Mon123.
I am happy to123!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strrep(char *raw, char const *tgt, char const *rep)
{
    char *p = strstr(raw, tgt);
    if (p == NULL)
    {
        return 0;
    }
    char seg0[4096];

    strncpy(seg0, raw, p - raw);
    sprintf(seg0 + (p - raw), "%s%s", rep, p + strlen(tgt));

    strcpy(raw, seg0);

    return 1;
}

int main(int argc, char const *argv[])
{
    FILE *fp_in, *fp_out;
    fp_in = fopen(argv[1], "r");
    if (fp_in == NULL)
    {
        exit(-1);
    }
    char content[4096];

    fread(content, sizeof(char), 4096, fp_in);

    fp_out = fopen("out.txt", "w");

    char const *tgt = argv[2], *rep = argv[3];
    while(strrep(content, tgt, rep));
    for (int i = 0; i < strlen(content); i++)
    {
        printf("%c %d\n", content[i], content[i]);
    }
    
    fwrite(content, sizeof(char), strlen(content), fp_out);
    fclose(fp_in);
    fclose(fp_out);
    return 0;
}
