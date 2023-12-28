/*
第3关：程序改错

任务描述
教材P106，程序改错第（1）题
本关任务：右侧是计算s=1!+2!+3!+...+n!的程序。程序中存在若干语法和逻辑错误，要求对程序进行修改，使其能够输出正确结果。

编程要求
根据提示，在右侧编辑器修改代码，使其能运行得到正确结果。

测试说明
平台会对你编写的代码进行测试：

测试输入：无
预期输出：
k=1 the sum is 1
k=2 the sum is 3
k=3 the sum is 9
...
k=20 the sum is 2561327494111820313

提示：

1<=n<=20

*/

#include <stdio.h>
long double sum_fac(int n);
int main(void)
{
	int k;
	for (k = 1; k <= 20; k++)
		printf("k=%d the sum is %.0Lf\n", k, sum_fac(k));
	return 0;
}
long double sum_fac(int n)
{
	long double s = 0, fac = 1.0;
	int i;
	for (i = 1; i <= n; i++)
	{
		fac *= i;
		s += fac;
	}
	return s;
}