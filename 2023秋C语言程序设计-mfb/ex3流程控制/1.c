#include <stdio.h>
int main()
{
	int i, x, k, flag = 0;
	//	printf("�������жϺ��������������1����������Ctrl+Z����\n");
	while (scanf("%d", &x) != EOF)
	{
		flag = 0;
		for (i = 2, k = x >> 1; i <= k; i++)
			if (!(x % i))
			{
				flag = 1;
				break;
			}
		if (flag == 1)
			printf("%d�Ǻ���\n", x);
		else
			printf("%d���Ǻ���\n", x);
	}
	return 0;
}