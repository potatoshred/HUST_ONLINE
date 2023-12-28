/*
第3关：源程序修改替换（二）
任务描述
实验教材P206 2.源程序修改替换 第（2）题
本关任务：修改替换create_list函数，将其建成一个后进先出的链表。

相关知识
为了完成本关任务，你需要掌握：1.结构体，2.链表。

编程要求
根据提示，在右侧编辑器补充代码，计算并输出数组的平均值和最大值。

测试说明
平台会对你编写的代码进行测试：

测试输入：1 2 3 4 5 6 7 8 0
预期输出：
8    7    6    5    4    3    2    1


测试输入：
1 2 3 4 5 6 7 8 0
—— 预期输出 ——
—— 实际输出 ——

8	7	6	5	4	3	2	1


测试输入：
122 103 99 88 66 34 12 0
—— 预期输出 ——
—— 实际输出 ——

12	34	66	88	99	103	122
*/

/*实验 7-1 修改替换题:创建后进先出链表*/
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
// 创建链表的函数定义
void create_list(struct s_list **headp, int *p)
{
    while (*p)
    {
        struct s_list *cur = (struct s_list *)malloc(sizeof(struct s_list)); // 分配内存给新节点
        cur->data = *p++; // 设置新节点的数据为数组元素值
        
        if (*headp == NULL) // 如果链表为空，新节点就是头节点
        {
            cur->next = NULL; // 将新节点的next指针设为空
        }
        else // 如果链表不为空，将新节点连接到链表头部
        {
            cur->next = *headp; // 新节点的next指向原头节点
        }
        *headp = cur; // 更新头节点为新节点
    }
}
