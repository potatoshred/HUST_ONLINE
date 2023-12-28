/*
第8关：二分查找

任务描述
实验指导书 P142 程序设计第（3）题
本关任务：对第（2）题的程序增加查找功能（功能编号4）：输入一个C语言课程成绩值，用二分查找进行搜索。如果查找到有该成绩，则输出该成绩所有学生的姓名和C语言课程的成绩；否则，输出提示"not found"。

示例
输入：
依次输入功能编号1，学生数量n，每个学生的姓名和成绩，功能编号2，二分查找4，查找的成绩x：
1
3
xiaoming 90
xiaohong 79
zhangsan 83
2
4 90
0
输出：（如果有多个，一行一个学生）
xiaoming 90


测试输入：
1
3
xiaoming 90
xiaohong 79
zhangsan 83
2
4 83
0
—— 预期输出 ——
—— 实际输出 ——

zhangsan 83

测试输入：
1
4
lisi 78
xiaoming 90
zhangsan 99
xiaohong 90
2
4 89
0
—— 预期输出 ——
—— 实际输出 ——

not found

测试输入：
1
4
lisi 78
xming 90
zhangsan 99
xhong 90
2
4 90
0
—— 预期输出 ——
—— 实际输出 ——

xhong 90
xming 90


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
    int num = 0;
    while (1)
    {
        int cmd = Get_cmd_id();
        if (cmd == 0) // quit
        {
            break;
        }
        else if (cmd == 1) // 输入
        {

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
            for (int i = 0; i < num - 1; i++)
            {
                for (int j = 0; j < num - 1 - i; j++)
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
        else if (cmd == 4)
        {
            // search
            int tgt, flag=0;
            scanf("%d", &tgt);
            for (int i = 0; i < num; i++)
            {
                int cur;
                char name[32];
                sscanf(sheet[i], "%3d%s", &cur, name);
                if (cur==tgt)
                {
                    flag=1;
                    printf("%s %d\n", name, tgt);
                }
                
            }
            if (!flag)
            {
                printf("not found");
            }
            
            
            // int left = 0, right = num - 1, mid;
            // char sscore[4];
            // sprintf(sscore, "%03d", tgt);
            // for (mid = (left + right) / 2; left < right && (strncmp(sheet[mid], sscore, 3) != 0); mid = (left + right) / 2)
            // {
            //     if (strncmp(sheet[mid], sscore, 3) == -1)
            //     {
            //         right = mid - 1;
            //     }
            //     else if (strncmp(sheet[mid], sscore, 3) == 1)
            //     {
            //         left = mid + 1;
            //     }
            //     else{
                    
            //     }
            // }

        }
    }

    return 0;
}
