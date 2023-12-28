/*
第12关：函数调度
任务描述
实验指导书P183 程序设计第（12）题

本关任务：函数调度。

输入输出示例
输入：
13607122

输出：
task1 is called!
task3 is called!
task6 is called!
task0 is called!
task7 is called!
task1 is called!
task2 is called!
task2 is called!
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TSKID(id) task##id
#define TSK(id) void TSKID(id)() { printf("task%s is called!\n", #id); }

TSK(0)
TSK(1)
TSK(2)
TSK(3)
TSK(4)
TSK(5)
TSK(6)
TSK(7)

void execute(void (*func_list[])(), int len)
{
    for (int i = 0; i < len; i++)
    {
        func_list[i]();
    }
}

void scheduler(int *index_list, void (**func_table)())
{
    char sequence[128];
    scanf("%s", sequence);
    int len = strlen(sequence);
    index_list = (int *)malloc(len * sizeof(int));
    for (int i = 0; i < len; i++)
    {
        index_list[i] = sequence[i] - '0';
    }
    void (**func_list)() = (void (**)())malloc(len * sizeof(void (*)()));
    for (int i = 0; i < len; i++)
    {
        func_list[i] = func_table[index_list[i]];
    }
    
    execute(func_list, len);

    free(index_list);
}

int main(int argc, char const *argv[])
{
    void (*func_table[])() = {task0, task1, task2, task3, task4, task5, task6, task7};
    int *index_list;
    scheduler(index_list, func_table);
    return 0;
}
