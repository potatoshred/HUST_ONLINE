#include <stdio.h>
int main()
{
	int i, x, k, flag = 0;
	//	printf("�������жϺ��������������1����������Ctrl+Z����\n");
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
			printf("%d�Ǻ���\n", x);
		else
			printf("%d���Ǻ���\n", x);
	}
	return 0;
}