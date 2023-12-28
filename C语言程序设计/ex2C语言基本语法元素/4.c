#include <stdio.h>

int main(int argc, char const *argv[])
{
    char phone[128];
    scanf("%s", phone);
    // printf("%s", phone);
    int length = 0;
    while (phone[length] != '\0')
    {
        length++;
    }
    if (length != 11)
    {
        printf("长度不合法");
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            printf("字符串中存在非数字字符");
            return 0;
        }
    }
    if (phone[0] != '1')
    {
        printf("第1位不合法");
        return 0;
    }
    if (phone[1] < '3')
    {
        printf("第2位不合法");
        return 0;
    }

    return 0;
}
