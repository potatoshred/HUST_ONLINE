/*
第8关：成绩排序（二）
任务描述
实验教材P208 程序设计 第（7）题
本关任务：
对于程序设计第三题，进一步写出用交换结点指针域的方法升序排序的函数。菜单选项：

输入每个学生的各项信息
输出每个学生的各项信息，结果按平均成绩升序排序
修改指定学生的指定数据项的内容：
修改英语成绩
修改高等数学成绩
修改普通物理成绩
修改C语言成绩
统计每个学生的平均成绩，结果按平均成绩升序排序（保留2位小数）
输出各位学生的学号、姓名、4门课程的总成绩和平均成绩，结果平均成绩升序排序
编程要求
根据题目要求，在右侧编辑器中完成程序设计。

测试说明
平台会对你编写的代码进行测试：

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
U202098765 Jerry 98 76 54 32
U202012345 Jack 98 76 54 32
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

typedef struct TEMP
{
    char uid[16];      // 学生ID
    char name[16];     // 学生姓名
    int scores[4];     // 学生成绩数组，包含4门科目的成绩
    int sum;           // 学生成绩总和
    double avg;        // 学生成绩平均值
    struct TEMP *next; // 下一个学生的指针
} STUDENTS;

// 记录学生信息并返回指向学生结构的指针
STUDENTS *Record()
{
    STUDENTS *tmp = (STUDENTS *)malloc(sizeof(STUDENTS)); // 为学生结构分配内存
    tmp->next = NULL;                                     // 设置下一个学生的指针为空
    // 从输入中读取学生信息
    scanf("%s %s %d %d %d %d", tmp->uid, tmp->name, &tmp->scores[0], &tmp->scores[1], &tmp->scores[2], &tmp->scores[3]);
    tmp->sum = (tmp->scores[0] + tmp->scores[1] + tmp->scores[2] + tmp->scores[3]); // 计算学生成绩总和
    tmp->avg = tmp->sum * .25;                                                      // 计算学生成绩平均值
    return tmp;                                                                     // 返回指向学生结构的指针
}

// 添加指定数量的新学生信息到链表中
void AddND(STUDENTS **students, int num)
{
    STUDENTS *cur = *students;    // 当前学生
    STUDENTS *head = NULL, *tail; // 头结点和尾结点
    head = Record();              // 记录第一个学生信息并作为头结点
    tail = head;                  // 尾结点指向头结点
    // 循环添加新学生到链表
    for (int i = 1; i < num; i++)
    {
        STUDENTS *tmp = Record(); // 记录新学生信息
        tail->next = tmp;         // 将新学生连接到链表尾部
        tail = tail->next;        // 更新尾结点
    }
    // 将新的学生链表连接到已有链表或设置为新的链表
    if (*students != NULL)
    {
        while (cur->next != NULL)
        {
            cur = cur->next;
        }
        cur->next = head; // 将新学生链表连接到已有链表的尾部
    }
    else
    {
        *students = head; // 设置新的链表
    }
}

// 计算学生链表中每个学生的平均成绩
void CalcAvg(STUDENTS *students)
{
    STUDENTS *cur = students; // 当前学生
    // 遍历链表计算每个学生的平均成绩
    while (cur != NULL)
    {
        cur->sum = (cur->scores[0] + cur->scores[1] + cur->scores[2] + cur->scores[3]); // 计算学生成绩总和
        cur->avg = cur->sum * .25;                                                      // 计算学生成绩平均值
        cur = cur->next;                                                                // 移动到下一个学生
    }
}

// 根据模式打印学生链表的信息
void PrintLN(STUDENTS *students, int mode)
{
    STUDENTS *cur = students; // 当前学生
    // 遍历链表并根据不同模式打印学生信息
    while (cur != NULL)
    {
        if (mode == 1)
        {
            printf("%s %s %d %d %d %d\n", cur->uid, cur->name, cur->scores[0], cur->scores[1], cur->scores[2], cur->scores[3]); // 打印学生详细信息
        }
        else if (mode == 2)
        {
            printf("%s %s %d %.2f\n", cur->uid, cur->name, cur->sum, cur->avg); // 打印学生总成绩和平均成绩
        }
        cur = cur->next; // 移动到下一个学生
    }
}

// 修改指定学生的指定科目成绩
void Modify(STUDENTS *students)
{
    char uid[16];                             // 学生ID
    int subject, score;                       // 科目和分数
    scanf("%s %d %d", uid, &subject, &score); // 读取输入的修改信息
    STUDENTS *cur = students;                 // 当前学生
    // 遍历链表查找要修改成绩的学生
    while (cur != NULL)
    {
        if (!strcmp(cur->uid, uid)) // 找到目标学生
        {
            cur->scores[subject - 1] = score; // 修改指定科目成绩
            return;
        }
        cur = cur->next; // 移动到下一个学生
    }
}
// 使用节点指针域调整链表顺序进行升序排序
void bubbleSort(STUDENTS **head) {
    int swapped;
    STUDENTS *ptr;
    STUDENTS *end = NULL;

    if (*head == NULL) {
        return;
    }

    do {
        swapped = 0;
        ptr = *head;

        while (ptr->next != end) {
            // 如果当前学生的平均成绩大于下一个学生的平均成绩，交换节点的指针域连接方式
            if (ptr->avg > ptr->next->avg ||(ptr->avg == ptr->next->avg && strcmp(ptr->name, ptr->next->name) > 0) ) {
                STUDENTS *tmp = ptr->next;
                ptr->next = tmp->next;
                tmp->next = ptr;

                if (ptr == *head) {
                    *head = tmp;
                } else {
                    // 找到前一个节点，并连接到交换后的节点
                    STUDENTS *prev = *head;
                    while (prev->next != ptr) {
                        prev = prev->next;
                    }
                    prev->next = tmp;
                }

                swapped = 1;
            }
            if (!swapped)
            {
                ptr = ptr->next;
            }
        }
        end = ptr;
    } while (swapped);
}

int main(int argc, char const *argv[])
{
    int cmd;                   // 命令
    STUDENTS *students = NULL; // 学生链表

    while (1)
    {
        int num;           // 数量
        scanf("%d", &cmd); // 读取命令

        switch (cmd) // 根据命令执行相应操作
        {
        case 1:
            scanf("%d", &num);     // 读取要添加的学生数量
            AddND(&students, num); // 添加新学生到链表
            bubbleSort(&students);  // 对新加入的学生进行排序
            break;
        case 2:
            PrintLN(students, 1); // 打印学生详细信息
            break;
        case 3:
            Modify(students);  // 修改学生信息
            CalcAvg(students); // 重新计算平均成绩
            bubbleSort(&students); // 对学生链表进行排序
            break;
        case 4:
            CalcAvg(students); // 计算学生平均成绩
            break;
        case 5:
            PrintLN(students, 2); // 打印学生总成绩和平均成绩
            break;
        default:
            return 0; // 结束程序
            break;
        }
    }

    return 0;
}
