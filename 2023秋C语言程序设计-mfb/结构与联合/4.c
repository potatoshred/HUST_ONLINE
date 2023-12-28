/*第4关：链表的使用


任务描述
本关任务：编程实现
（1）用一个单向链表接收一个长字符串，且每个节点接收一个字符，遍历输出链表中的所有字符，并将字符串无冗余地存放到一个动态存储分配的的字符数组中，并且输出该字符串。（本题暂不考虑空字符串情况）(结尾以回车结束)
（2）再输入一个字符，如果该字符已在链表中，则删除该结点，否则在输入字符和结点的数据域字符差值最小的结点后面插入包含该字符的结点，输出最后的字符串。

要求：采用模块化设计方法，将创建链表、遍历链表、删除结点、插入结点等功能用函数实现。

测试说明
平台会对你编写的代码进行测试，若是与预期输出相同，则算通关。

测试输入：
qwertyuiopasdfghjkl
i
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
qwertyuopasdfghjkl

测试输入：
qwertyuiopasdfghjkl
q
预期输出：
q w e r t y u i o p a s d f g h j k l
qwertyuiopasdfghjkl
wertyuiopasdfghjkl

测试输入：
qwer1234?@%
5
预期输出：
q w e r 1 2 3 4 ? @ %
qwer1234?@%
qwer12345?@%
*/

/**********  Begin  **********/
#include <stdio.h>
#include <stdlib.h>

struct node
{
    char c;
    struct node *node_next;
};

struct node *node_create()
{
    struct node *node_head = NULL, *node_tail = NULL, *node_tmp = NULL;
    char c;
    while ((c = getchar()) != '\n')
    {
        node_tmp = (struct node *)malloc(sizeof(struct node));
        node_tmp->c = c;
        node_tmp->node_next = NULL;
        if (node_head == NULL)
        {
            node_head = node_tmp;
            node_tail = node_tmp;
        }
        else
        {
            node_tail->node_next = node_tmp;
            node_tail = node_tmp;
        }
    }
    return node_head;
}

int node_cnt(struct node *node_head)
{
    struct node *node_tmp = node_head;
    int cnt = 1;
    while (node_tmp->node_next != NULL)
    {
        cnt++;
        node_tmp = node_tmp->node_next;
    }
    return cnt;
}

char *node_to_arr(struct node *node_head)
{
    int cnt = node_cnt(node_head);
    char *table = malloc(cnt * sizeof(char));

    struct node *node_tmp = node_head;
    for (int i = 0; i < cnt; i++)
    {
        table[i] = node_tmp->c;
        node_tmp = node_tmp->node_next;
    }

    return table;
}

void node_print(struct node *node_head, char *sep)
{
    struct node *node_tmp = node_head;
    while (node_tmp->node_next != NULL)
    {
        putchar(node_tmp->c);
        printf("%s", sep);
        node_tmp = node_tmp->node_next;
    }
    putchar(node_tmp->c);
    printf("%s", sep);
}

char find_nearest(char c, struct node *node_head)
{
    int cnt = node_cnt(node_head);
    char *table = node_to_arr(node_head);

    int gap, min_gap = -256;
    for (int i = 0; i < cnt; i++)
    {
        gap = table[i] - c;
        min_gap = (min_gap * min_gap < gap * gap) ? min_gap : gap;
    }
    return c + min_gap;
}

struct node *node_del(char c_del, struct node *node_head)
{
    while (node_head->c == c_del)
    {
        node_head = node_head->node_next;
    }

    struct node *node_tmp = node_head;
    struct node *node_prev = node_head;
    while (node_tmp->node_next != NULL)
    {
        if (node_tmp->c == c_del)
        {
            node_prev->node_next = node_tmp->node_next;
            free(node_tmp);
            node_tmp = node_prev->node_next;
        }
        else
        {
            node_prev = node_tmp;
            node_tmp = node_tmp->node_next;
        }
    }

    if (node_tmp->c == c_del)
    {
        free(node_tmp);
        node_prev->node_next = NULL;
    }

    return node_head;
}

struct node *node_add(char c_add, char c_add_before, struct node *node_head)
{
    struct node *node_tmp = node_head;
    struct node *node_prev = node_head;
    while (node_tmp->node_next != NULL)
    {
        if (node_tmp->c == c_add_before)
        {
            struct node *node_insert = (struct node *)malloc(sizeof(struct node));
            node_insert->c = c_add;
            node_insert->node_next = node_tmp->node_next;
            node_tmp->node_next = node_insert;
        }

        node_tmp = node_tmp->node_next;
    }
    if (node_tmp->c == c_add_before)
    {
        struct node *node_insert = (struct node *)malloc(sizeof(struct node));
        node_insert->c = c_add;
        node_insert->node_next = NULL;
        node_tmp->node_next = node_insert;
    }
    return node_head;
}

int main(int argc, char const *argv[])
{
    struct node *node_head = node_create();
    int cnt = node_cnt(node_head);
    char *table = node_to_arr(node_head);

    char eliminate;
    scanf("%c", &eliminate);

    node_print(node_head, " "), putchar('\n');
    node_print(node_head, ""), putchar('\n');

    char nearest = find_nearest(eliminate, node_head);

    if (nearest == eliminate)
    {
        node_head = node_del(eliminate, node_head);
    }
    else
    {
        node_head = node_add(eliminate, nearest, node_head);
    }

    node_print(node_head, "");

    return 0;
}
