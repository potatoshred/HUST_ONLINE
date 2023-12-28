#include <stdio.h>

struct student
{
    int num;
    char name[12];
    double score;
};

/****在下面定义函数scan，对结构数组初始化******/
void scan(struct student *p, int n)
{
    /**********  Begin  **********/
    for (int i = 0; i < n; i++)
    {
        scanf("%d %s %lf", &p->num, &p->name, &p->score);
        p++;
    }
    /**********  End  **********/
}

/****在下面定义函数print，依次输出结构数组的各成员值******/
void print(struct student *p, int n)
{
    /**********  Begin  **********/
    for (int i = 0; i < n; i++)
    {
        printf("%d %s %.1lf\n", p->num, p->name, p->score);
        p++;
    }
    
    /**********  End  **********/
}

#define N 3
int main()
{
    struct student s[N];
    scan(s, N);
    print(s, N);
    return 0;
}
