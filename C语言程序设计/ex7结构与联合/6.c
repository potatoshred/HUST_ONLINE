/*
第6关：成绩排序（一）
任务描述
实验教材P207 程序设计 第（3）题
本关任务：
对程序设计的第二题增加按照平均成绩进行升序排序的函数，写出用交换结点数据域的方法升序排序的函数，排序可用选择法或冒泡法。菜单选项：

退出
输入每个学生的各项信息
输出每个学生的各项信息，结果按平均成绩升序排序
修改指定学生的指定数据项的内容：
修改英语成绩
修改高等数学成绩
修改普通物理成绩
修改C语言成绩
统计每个学生的平均成绩，结果按平均成绩升序排序（保留2位小数）
输出各位学生的学号、姓名、4门课程的总成绩和平均成绩，结果平均成绩升序排序
相关知识
为了完成本关任务，你需要掌握：1.排序，2.链表。

编程要求
根据题目要求，在右侧编辑器完成程序设计。

测试说明
测试输入：
依次输入功能编号1，学生数量n，每个学生的学号、姓名和成绩；功能编号2；功能编号3，指定学生的学号，修改的数据项，数据；功能编号4；功能编号5：
1    （功能编号）
4    （学生人数）
U202012345 Jack 99 100 80 96    （学号 姓名 英语 数学 物理 C语言成绩）
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
2    （功能编号）
3    （功能编号）
U202054321 1 66    （将学号为U202054321的同学的英语成绩修改为66）
4    （功能编号）
5    （功能编号）

预期输出：

U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100
U202098765 Jerry 98 76 54 32
U202056789 Tom 12 34 56 78
U202012345 Jack 93.75
U202054321 Rose 86.25
U202098765 Jerry 65.00
U202056789 Tom 45.00
U202012345 Jack 375 93.75
U202054321 Rose 345 86.25
U202098765 Jerry 260 65.00
U202056789 Tom 180 45.00


测试输入：
1
2
U202054321 Rose 89 94 85 100
U202012345 Jack 99 100 80 96
2
3
U202054321 1 66
4
5
0
—— 预期输出 ——
—— 实际输出 ——

U202054321 Rose 89 94 85 100
U202012345 Jack 99 100 80 96
U202054321 Rose 86.25
U202012345 Jack 93.75
U202054321 Rose 345 86.25
U202012345 Jack 375 93.75


测试输入：
1
4
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202012345 Jack 99 100 80 96
U202098765 Jerry 98 76 54 32
2
3
U202054321 1 66
4
5
0
—— 预期输出 ——
—— 实际输出 ——

U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
U202054321 Rose 89 94 85 100
U202012345 Jack 99 100 80 96
U202056789 Tom 45.00
U202098765 Jerry 65.00
U202054321 Rose 86.25
U202012345 Jack 93.75
U202056789 Tom 180 45.00
U202098765 Jerry 260 65.00
U202054321 Rose 345 86.25
U202012345 Jack 375 93.75
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stu
{
    char uid[11];
    char name[16];
    int scores[4];
    double score_avg;
    struct Stu *Stu_next;
};

int Get_func_id()
{
    int n;
    scanf("%d", &n);
    getchar();
    return n;
}

void Node_append(struct Stu **head, struct Stu *newnode)
{
    if (*head == NULL)
    {
        *head = newnode;
        return;
    }
    
    struct Stu *tmp = *head;
    while (tmp->Stu_next != NULL)
    {
        tmp = tmp->Stu_next;
    }
    tmp->Stu_next = newnode;
}

void Node_swap_data(struct Stu *sb, struct Stu *sb_next)
{
    // struct Stu *sb_next = sb->Stu_next;

    // swap uid
    char uid_tmp[11];
    strcpy(uid_tmp, sb->uid);
    strcpy(sb->uid, sb_next->uid);
    strcpy(sb_next->uid, uid_tmp);

    // swap name
    char name_tmp[16];
    strcpy(name_tmp, sb->name);
    strcpy(sb->name, sb_next->name);
    strcpy(sb_next->name, name_tmp);

    // swap scores
    for (int i = 0; i < 4; i++)
    {
        int tmp = sb->scores[i];
        sb->scores[i] = sb_next->scores[i];
        sb_next->scores[i] = tmp;
    }

    // swap average
    double tmp = sb->score_avg;
    sb->score_avg = sb_next->score_avg;
    sb_next->score_avg = tmp;
}

void Node_sort(struct Stu *sheet_head)
{
    struct Stu *current = sheet_head;
    struct Stu *index = NULL;

    if (sheet_head == NULL)
    {
        return;
    }

    while (current != NULL)
    {
        index = current->Stu_next;
        while (index != NULL)
        {
            if (current->score_avg > index->score_avg)
            {
                Node_swap_data(index, current);
            }
            index = index->Stu_next;
        }
        current = current->Stu_next;
    }
    return;
}

void Print_detail(struct Stu *sheet_head)
{
    struct Stu *tmp = sheet_head;
    if (sheet_head == NULL)
    {
        return;
    }
    while (tmp != NULL)
    {
        printf("%s %s %d %d %d %d\n",
               tmp->uid, tmp->name,
               tmp->scores[0],
               tmp->scores[1],
               tmp->scores[2],
               tmp->scores[3]);
        tmp = tmp->Stu_next;
    }
    return;
}

void Print_average_each(struct Stu *sheet_head)
{
    struct Stu *tmp = sheet_head;
    if (sheet_head == NULL)
    {
        return;
    }

    while (tmp != NULL)
    {
        double avg = 0;
        avg = 0.25 * (tmp->scores[0] + tmp->scores[1] + tmp->scores[2] + tmp->scores[3]);
        printf("%s %s %.2lf\n", tmp->uid, tmp->name, avg);
        tmp = tmp->Stu_next;
    }
    return;
}

void Print_average_total_each(struct Stu *sheet_head)
{
    struct Stu *tmp = sheet_head;
    if (sheet_head == NULL)
    {
        return;
    }

    while (tmp != NULL)
    {
        int avg = 0;
        avg = (tmp->scores[0] + tmp->scores[1] + tmp->scores[2] + tmp->scores[3]);
        printf("%s %s %d %.2lf\n", tmp->uid, tmp->name, avg, 0.25 * avg);
        tmp = tmp->Stu_next;
    }
    return;
}

int main(int argc, char const *argv[])
{
    struct Stu *students = NULL;

    while (1)
    {
        int cmd = Get_func_id();
        if (cmd == 0)
        {
            break;
        }
        else if (cmd == 1)
        {
            int num = Get_func_id();

            for (int i = 0; i < num; i++)
            {
                struct Stu *tmp = (struct Stu *)malloc(sizeof(struct Stu));
                tmp->Stu_next = NULL;

                char line[128];
                fgets(line, 128, stdin);
                sscanf(line, "%s %s %d %d %d %d", tmp->uid, tmp->name,
                       &(tmp->scores[0]), &(tmp->scores[1]), &(tmp->scores[2]), &(tmp->scores[3]));
                tmp->score_avg = (tmp->scores[0] + tmp->scores[1] + tmp->scores[2] + tmp->scores[3]) * 0.25;
                Node_append(&students, tmp);
            }
            
            Node_sort(students);
            // Node_sort(students);
        }
        else if (cmd == 2)
        {
            Print_detail(students);
        }
        else if (cmd == 3)
        {
            struct Stu *tmp = students;
            char uid[16];
            int index, score;
            scanf("%s %d %d", uid, &index, &score);
            while (tmp != NULL)
            {
                if (strcmp(tmp->uid, uid) == 0)
                {
                    tmp->scores[index - 1] = score;
                    break;
                }
                else
                {
                    tmp = tmp->Stu_next;
                }
            }
        }
        else if (cmd == 4)
        {
            Print_average_each(students);
        }
        else if (cmd == 5)
        {
            Print_average_total_each(students);
        }
    }

    return 0;
}
