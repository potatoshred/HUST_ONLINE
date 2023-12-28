/*
第2关：程序完善和修改替换--字符串排序（填空）
任务描述
本关任务：实验教材P179 6.3.2节 2.程序完善和修改替换 第（1）题
strsort用于对字符串进行升序排序，再主函数中输入N个字符串存入通过malloc动态分配的存储空间，然后调用strsort对这N个串按字典升序排序。

请填写合适代码完善程序

示例
输入：首先输入N，然后输入N个字符。
3
C
Python
Java
输出：
C
Java
Python
*/
/* 实验6程序完善与修改替换第（1）题源程序：字符串升序排序 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* 对指针数组s指向的size个字符串进行升序排序 */
void strsort(char *s[], int size)
{
    char *temp;
    int i, j;

    for (i = 0; i < size - 1; i++)
        for (j = 0; j < size - i - 1; j++)
        {
            int k = 0;
            while (1)
            {
                if (s[j][k] > s[j + 1][k])
                {
                    temp = s[j];
                    s[j] = s[j + 1];
                    s[j + 1] = temp;
                    break;
                }else if (s[j][k] == s[j + 1][k])
                {
                    k++;
                }else
                {
                    break;
                }
                
                
            }
        }
}

int main()
{
    int i;
    int N;
    scanf("%d", &N);
    char **s = (char **)malloc(N * sizeof(char *));
    char t[50];
    for (i = 0; i < N; i++)
    {
        scanf("%s", t);
        s[i] = (char *)malloc((strlen(t) + 1) * sizeof(char));
        strcpy(s[i], t);
    }
    strsort(s, N);
    for (i = 0; i < N; i++)
        puts(s[i]);
    return 0;
}
