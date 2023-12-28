/*
??7关：回文字符??
任务描述
实验教材P207 程序设计 第（4）题
本关任务??
回文字符串是正读和反读都相同的字符串，例如“abba”和“abcba”是回文字符串。设计程序判断输入的任意长度的字符串是否为回文字符串??
提示：由于要求字符串长度任意，所以用单链表存储字符串，即判断一个单链表是否为回文链表??

编程要求
根据题目要求，在右侧编辑器中两个函数的算法设计??

void createLinkList(C_NODE **headp, char s[]) 根据字符串s构造单链表，得到一个以单链表表示的字符串，单链表结点定义见右侧编辑器??
void judgePalindrome(C_NODE *head) 判断以head为头指针的单链表表示的字符串是否为回文，是则显示true，否则显示false??
测试说明
平台会对你编写的代码进行测试??

测试输入1??
ababa
预期输出1??
true

测试输入2??
race a car
预期输出2??
false

测试输入2??
happycoding!
预期输出2??
false


测试输入??
ppoqq
—?? 预期输出 —??
—?? 实际输出 —??

false


测试输入??
A man a plan aca nalp a nam A
—?? 预期输出 —??
—?? 实际输出 —??

true



*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct c_node
{
    char data;
    struct c_node *next;
} C_NODE;

// 创建单链表
void createLinkList(C_NODE **headp, char s[])
{
    /********** 创建单链表 **********/
    C_NODE *cur = *headp = NULL; // 初始化当前节点和头节点为NULL
    int i = 0;
    while (s[i] != '\0') // 遍历输入字符串
    {
        C_NODE *new_node = (C_NODE *)malloc(sizeof(C_NODE)); // 为新节点分配内存
        new_node->data = s[i]; // 设置新节点的数据为字符串中的字符
        new_node->next = NULL; // 将新节点的next指针设为NULL

        if (*headp == NULL) // 如果头节点为空，将新节点设置为头节点并更新当前节点
        {
            *headp = cur = new_node;
        }
        else // 否则将新节点连接到链表末尾
        {
            cur->next = new_node;
            cur = new_node;
        }

        i++;
    }
    /********** 创建单链表 **********/
}

// 判断是否为回文链表
void judgePalindrome(C_NODE *head)
{
    /********** 判断回文链表 **********/
    C_NODE *cur = head; // 初始化当前节点为头节点
    C_NODE *slow, *fast, *prev = NULL; // 初始化指针变量
    slow = fast = cur; // 初始化慢指针和快指针为头节点
    while (fast != NULL && fast->next != NULL) // 使用快慢指针找到链表中点
    {
        fast = fast->next->next;
        cur = slow->next;
        slow->next = prev;
        prev = slow;
        slow = cur;
    }

    if (fast) // 如果链表节点数为奇数，调整慢指针位置
    {
        slow = slow->next;
    }
    while (slow != NULL) // 检查回文性质
    {
        if (slow->data != prev->data)
        {
            printf("false");
            return;
        }
        slow = slow->next;
        prev = prev->next;
    }
    printf("true");
    /********** 判断回文链表 **********/
}

int main()
{
    char s[1000], *pc = s; // 初始化输入字符串和指向字符串的指针
    int len = 0;
    C_NODE *head, *p; // 初始化链表头节点和遍历节点

    scanf("%[^\n]", s); // 读取输入字符串直到换行符为止

    createLinkList(&head, s); // 创建单链表

    for (p = head; p; p = p->next) // 计算单链表长度
        len++;
    if (len != strlen(s)) // 检查单链表长度与输入字符串长度是否一致
    {
        printf("单链表长度不正确");
        return 1;
    }
    else // 如果长度一致，检查单链表内容是否与输入字符串一致
    {
        for (p = head; p; p = p->next)
        {
            if (p->data != *pc++)
            {
                printf("单链表有错误结点");
                return 1;
            }
        }
    }
    
    judgePalindrome(head); // 判断链表是否为回文链表
    return 0;
}
