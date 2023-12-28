#include<stdio.h>
struct date{
    int year;
    int month;
    int day;
};
int main()
{
    /**********  Begin  **********/
    struct date date1;
    int flag=0;//标记闰年
    int sum=0;//输出结果
    int days[2][12]={{31,28,31,30,31,30,31,31,30,31,30,31},{31,29,31,30,31,30,31,31,30,31,30,31}};
    scanf("%d %d %d",&date1.year,&date1.month,&date1.day);
    if((date1.year%4==0&&date1.year%100!=0)||(date1.year%400==0))
        flag=1;//判断闰年
    if(date1.day>0&&date1.day<=days[flag][date1.month-1]&&date1.month>0&&date1.month<=12)
    {
        for(int n=0;n<date1.month-1;n++)
            sum+=days[flag][n];
        sum+=date1.day;
        printf("%d",sum);
    }
    else
        printf("不存在这样的日期");
    /**********   End   **********/
    return 0; 
}