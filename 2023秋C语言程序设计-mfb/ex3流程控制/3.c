#include <stdio.h>
int main()
{
	int i, x, k, flag = 0;
	//	printf("本程序判断合数，请输入大于1的整数，以Ctrl+Z结束\n");
	while (scanf("%d", &x) != EOF)
	{
		flag = 0;
		i = 2, k = x >> 1;
		do
		{
			if (!(x % i) && x > 2)
			{
				flag = 1;
				break;
			}
		} while ((i++) <= k);

		if (flag == 1)
			printf("%d是合数\n", x);
		else
			printf("%d不是合数\n", x);
	}
	return 0;
}