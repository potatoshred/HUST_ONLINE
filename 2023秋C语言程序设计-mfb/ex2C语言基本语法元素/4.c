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
        printf("���Ȳ��Ϸ�");
        return 0;
    }

    for (int i = 0; i < 11; i++)
    {
        if (phone[i] < '0' || phone[i] > '9')
        {
            printf("�ַ����д��ڷ������ַ�");
            return 0;
        }
    }
    if (phone[0] != '1')
    {
        printf("��1λ���Ϸ�");
        return 0;
    }
    if (phone[1] < '3')
    {
        printf("��2λ���Ϸ�");
        return 0;
    }

    return 0;
}
