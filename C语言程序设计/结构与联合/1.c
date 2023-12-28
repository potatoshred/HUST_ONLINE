#include <stdio.h>
/**********  Begin  **********/
struct date
{
	int year;
	int month;
	int day;
};
int is_leap(int year)
{
	return (!(year % 4) && (year % 100)) || (!(year % 400));
}

int main()
{
	struct date D;
	scanf("%d", &D.year);
	scanf("%d", &D.month);
	scanf("%d", &D.day);

	int table[12] = {31,28,31,30,31,30,31,31,30,31,30,31};
	int sum=0;
	for (int i = 0; i < D.month-1; i++)
	{
		sum+=table[i];
	}
	sum+=D.day;
	if (is_leap(D.year)&&D.month>2)
	{	
		sum++;
	}

	if (D.month>12||D.month<0||D.day>table[D.month-1])
	{
		printf("不存在这样的日期");
		return 0;
	}
	

	printf("%d", sum);
	/**********   End   **********/
	return 0;
}