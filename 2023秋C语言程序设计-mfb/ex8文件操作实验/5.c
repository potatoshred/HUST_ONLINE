/*
第5关：班级成绩单3.(2)
任务描述
本关任务：对实验七程序设计第2题的程序，增加文件保存和文件打开的功能选项，用函数实现这两个功能。在原有功能选项的基础上，增加6、7两项功能。
0.退出
1.输入每个学生的各项信息
2.输出每个学生的各项信息
3.修改指定学生的指定数据项的内容：
    1.修改英语成绩
    2.修改高等数学成绩
    3.修改普通物理成绩
    4.修改C语言成绩
4.统计每个学生的平均成绩（保留2位小数）
5.输出各位学生的学号、姓名、4门课程的总成绩和平均成绩
6.文件保存功能：将链表结点中学生的各项信息保存到二进制文件stu.dat
7.文件打开功能：从文件stu.dat中读取学生信息到内存建立链表。

可以选择原题中的输出功能将这些信息显示在平面上，以验证读写操作的正确性。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，输入为功能编号，：

测试输入：
依次输入功能编号1，学生数量n，每个学生的学号、姓名和成绩；功能编号3，指定学生的学号，修改的数据项，数据；功能编号6，保存文件；功能编号7，从文件中读数据；功能编号4；功能编号5：
1    （功能编号）
4    （学生人数）
U202012345 Jack 99 100 80 96    （学号 姓名 英语 数学 物理 C语言成绩）
U202054321 Rose 89 94 85 100
U202056789 Tom 12 34 56 78
U202098765 Jerry 98 76 54 32
3    （功能编号）
U202054321 1 66    （将学号为U202054321的同学的英语成绩修改为66）
6    （功能编号）
7    （功能编号）
4    （功能编号）
5    （功能编号）

预期输出：

U202012345 Jack 93.75
U202054321 Rose 86.25
U202056789 Tom 45.00
U202098765 Jerry 65.00
U202012345 Jack 375 93.75
U202054321 Rose 345 86.25
U202056789 Tom 180 45.00
U202098765 Jerry 260 65.00

测试输入：
1
2
U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100
6
7
2
0
—— 预期输出 ——
—— 实际输出 ——

U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100


测试输入：
1
3
U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100
U202052764 Reem 87 92 88 99
6
7
2
0
—— 预期输出 ——
—— 实际输出 ——

U202012345 Jack 99 100 80 96
U202054321 Rose 89 94 85 100
U202052764 Reem 87 92 88 99
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Stu
{
    char uid[11];
    char name[16];
    int scores[4];
    struct Stu *Stu_next;
};
int Get_func_id()
{
    int n;
    scanf("%d", &n);
    getchar();
    return n;
}
void Print_detail(struct Stu *sheet_head)
{
    struct Stu *tmp = sheet_head;
    if (sheet_head == NULL)
    {
        return;
    }
    while (tmp->Stu_next != NULL)
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

    while (tmp->Stu_next != NULL)
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

    while (tmp->Stu_next != NULL)
    {
        int avg = 0;
        avg = (tmp->scores[0] + tmp->scores[1] + tmp->scores[2] + tmp->scores[3]);
        printf("%s %s %d %.2lf\n", tmp->uid, tmp->name, avg, 0.25 * avg);
        tmp = tmp->Stu_next;
    }
    return;
}

void Stu_writeline(FILE *fp, struct Stu *student)
{
    fprintf(fp, "%s %s %d %d %d %d\n",
            student->uid,
            student->name,
            &(student->scores[0]),
            &(student->scores[1]),
            &(student->scores[2]),
            &(student->scores[3]));
}

void Data_save(FILE *fp, struct Stu *sheet_head)
{
    rewind(fp);
    struct Stu *tmp = sheet_head;
    while (tmp->Stu_next != NULL)
    {
        Stu_writeline(fp, tmp);
        tmp = tmp->Stu_next;
    }
}

void Data_read(FILE *fp, struct Stu *sheet_head)
{
    rewind(fp);
    struct Stu *tmp = sheet_head;
    while (1)
    {
        char line[128];
        fgets(line, 128, fp);
        if (strlen(line) > 10)
        {

            sscanf(line, "%s %s %d %d %d %d\n",
                   tmp->uid,
                   tmp->name,
                   &(tmp->scores[0]),
                   &(tmp->scores[1]),
                   &(tmp->scores[2]),
                   &(tmp->scores[3]));
            tmp->Stu_next = (struct Stu *)malloc(sizeof(struct Stu));
            tmp = tmp->Stu_next;
            tmp->Stu_next = NULL;
        }
        else
        {
            break;
        }
    }
}
int main(int argc, char const *argv[])
{
    struct Stu *students = (struct Stu *)malloc(sizeof(struct Stu));
    struct Stu *tail = students;

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

            struct Stu *tmp = tail;
            char line[128];
            tmp->Stu_next = NULL;

            for (int i = 0; i < num; i++)
            {

                fgets(line, 128, stdin);
                sscanf(line, "%s %s %d %d %d %d", tmp->uid, tmp->name,
                       &(tmp->scores[0]), &(tmp->scores[1]), &(tmp->scores[2]), &(tmp->scores[3]));

                tmp->Stu_next = (struct Stu *)malloc(sizeof(struct Stu));
                tmp = tmp->Stu_next;
                tmp->Stu_next = NULL;
            }
            tail = tmp;
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
        else if (cmd == 6)
        {
            FILE *fp_save = fopen("stu.dat", "w");
            Data_save(fp_save, students);
        }
        else if (cmd == 7)
        {
            FILE *fp_read = fopen("stu.dat", "r");
            Data_read(fp_read, students);
        }
    }

    return 0;
}
