#include <stdio.h>

/**
  按任务要求补全该函数
  用递归实现辗转相除法
 **/
int gcd(int x, int y)
{
	/**********  Begin  **********/
	printf("%d %d\n", x, y);
	if (y)
	{
		int max, min, tmp;
		max = (x > y) ? x : y;
		min = (x < y) ? x : y;
		tmp = max % min;
		return gcd(min, tmp);
	}
	else
	{
		return x;
	}

	/**********  End  **********/
}

// 请根据此主函数流程，使用递归补全step6_stu.h文件中gcd()函数

int main()
{
	int x, y;

	scanf("%d%d", &x, &y);
	printf("%d", gcd(x, y));

	return 0;
}