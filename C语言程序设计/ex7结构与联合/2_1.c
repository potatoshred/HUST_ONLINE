/*
第2关：源程序修改替换（一）
任务描述
实验教材P206 2.源程序修改替换 第（1）题
    给定一批整数，以 0 为结束标志且不作为结点，将其建成一个先进先出的链表，先进先出链表的头指针始终指向最先创建的结点（链头），先建结点指向后建结点，后建结点始终是尾结点。

本关任务：
   对源程序进行修改、调试，使之能够正确完成指定任务。本题在书中源程序的基础上做以下改动：通过键盘输入给数组s的元素赋值，以0结束输入，且0作为数组的最后一个元素。

相关知识
为了完成本关任务，你需要掌握：1.结构体，2.链表。

编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试：

测试输入：1 2 3 4 5 6 7 8 0
预期输出：
1    2    3    4    5    6    7    8

测试输入：
1	2	3	4	5	6	7	8   0
—— 预期输出 ——
—— 实际输出 ——

1	2	3	4	5	6	7	8



测试输入：
12  34  66  88  99 103  122   0
—— 预期输出 ——
—— 实际输出 ——

12	34	66	88	99	103	122
*/

/*实验 7-1 修改替换题:创建先进先出链表*/
#include <stdio.h>
#include <stdlib.h>
struct s_list
{
    int data;            /*数据域*/
    struct s_list *next; /*指针域*/
};
void create_list(struct s_list **headp, int *p);
int main(void)
{
    struct s_list *head = NULL, *p;
    int s[] = {1, 2, 3, 4, 5, 6, 7, 8, 0}; /*0作为结束标记*/
    create_list(&head, s);
    p = head;
    while (p)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");
    return 0;
}
void create_list(struct s_list **headp, int *p)
{
    struct s_list *loc_head = NULL, *tail;
    if (p[0] == 0)
        ;
    else
    {
        loc_head = (struct s_list *)malloc(sizeof(struct s_list));
        loc_head->data = *p++;
        tail = loc_head;
        while (*p)
        {
            tail->next = (struct s_list *)malloc(sizeof(struct s_list));
            tail = tail->next;
            tail->data = *p++;
        }
        tail->next = NULL;
    }
    *headp = loc_head;
}
