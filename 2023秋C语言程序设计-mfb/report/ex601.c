/*
Input a string:
programming↙	(键盘输入)
programming
Input a string again;
language↙	(键盘输入)
language
*/

/* 实验 6-1程序改错与跟踪题源序 */

#include <stdio.h>
char *strcopy(char *, const char *);
int main(void)
{
    char *s1, *s2, *s3;
    printf("Input a string:\n", s2);
    scanf("%s", s2);
    strcopy(s1, s2);
    printf("%s\n", s1);
    printf("Input a string again:\n", s2);
    scanf("%s", s2);
    s3 = strcopy(s1, s2);
    printf("%s\n", s3);
    return 0;
}
/* 将字符串 s 复制给字符串 ,并且返回串的首地址 */
char *strcopy(char *t, const char *s)
{
    while (*t++ = *s++)
        ;
    return (t);
}