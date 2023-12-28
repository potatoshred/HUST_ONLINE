/*
第7关：成绩排序
任务描述
实验指导书 P142 程序设计第（2）题
本关任务：编写一个C程序，要求采用模块化设计思想，将相关功能用函数实现，并提供菜单选项，每次程序运行结束后需通过功能0退出程序。该程序具有以下功能：

退出程序；
输入n个学生的姓名和C语言课程的成绩；
将成绩按从高到低的次序排序，姓名同时进行相应调整（成绩相同的按姓名首字母排序，首字母相同的按第二个字母排序，依次类推）；
输出所有学生的姓名和C语言课程的成绩。
示例
输入1：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号3：
1          (功能编号)
3          (学生人数)
xiaoming 90   (学生姓名和成绩)
xiaohong 79
zhangsan 83
3               (功能编号)
0                (功能编号)
输出1：
xiaoming 90
xiaohong 79
zhangsan 83

输入2：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号2，功能编号3：
1          (功能编号)
3          (学生人数)
xiaoming 79   (学生姓名和成绩)
xiaohong 79
zhangsan 83
2   (功能编号，成绩相同的按姓名排序)
3   (功能编号)
0       (功能编号)

输出2：
zhangsan 83
xiaohong 79
xiaoming 79


测试输入：
1
3
a 90
b 70
c 85
3
0
—— 预期输出 ——
—— 实际输出 ——

a 90
b 70
c 85


测试输入：
1
4
ming 80
jerry 89
hong 80
angel 87
2
3
0
—— 预期输出 ——
—— 实际输出 ——

jerry 89
angel 87
hong 80
ming 80

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int Get_cmd_id()
{
    int x;
    scanf("%d", &x);
    getchar();
    return x;
}

void Swap_row(char *row1, char *row2)
{
    for (int i = 0; i < 32; i++)
    {
        char c = row1[i];
        row1[i] = row2[i];
        row2[i] = c;
    }
}

int main(int argc, char const *argv[])
{
    char sheet[128][32] = {{0}};
    while (1)
    {
        int cmd = Get_cmd_id();
        if (cmd == 0) // quit
        {
            break;
        }
        else if (cmd == 1) // 输入
        {
            int num;
            scanf("%d", &num);
            int score;
            char name[32];
            for (int i = 0; i < num; i++)
            {
                scanf("%s %d", name, &score);
                sprintf(sheet[i], "%03d%s", score, name);
            }
        }
        else if (cmd == 2)
        {
            for (int i = 0; i < 127; i++)
            {
                for (int j = 0; j < 127 - i; j++)
                {

                    for (int k = 0; k < 32; k++)
                    {

                        if (sheet[j][k] == sheet[j + 1][k])
                        {
                            continue;
                        }
                        if (k < 3)
                        {
                            if (sheet[j][k] > sheet[j + 1][k])
                            {
                                break;
                            }
                            else
                            {
                                Swap_row(sheet[j], sheet[j + 1]);
                                break;
                            }
                        }
                        else
                        {
                            if (sheet[j][k] < sheet[j + 1][k])
                            {
                                break;
                            }
                            else
                            {
                                Swap_row(sheet[j], sheet[j + 1]);
                                break;
                            }
                        }
                        
                    }
                }
            }
        }
        else if (cmd == 3)
        {
            for (int i = 0; i < 128; i++)
            {
                if (sheet[i][1])
                {
                    int score;
                    char name[32];
                    sscanf(sheet[i], "%3d%s", &score, name);
                    printf("%s %d\n", name, score);
                }
            }
        }
    }

    return 0;
}
