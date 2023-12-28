/*
第5关：程序修改替换(2)

任务描述
实验课本 P107 程序修改替换第（2）题
本关任务：修改实验教材P96例4.6中的sum和fun函数，使之计算量最小

编程要求
使得修改后的sum函数和func函数计算量最小

测试说明
平台会对你编写的代码进行测试：

测试输入：1 2
预期输出：The result is 2.500000

测试输入：3.5 4
预期输出：The result is 24.023438

提示：

使用局部静态变量
*/
#include <stdio.h>

double mulx(double x, int n);
long long frac(int n);

double sum(double x, int n)
{
	int i;
	double z = 1.0;
	for (i = 1; i <= n; i++)
	{
		z += mulx(x, i) / frac(i);
	}
	return z;
}

double mulx(double x, int n)
{
	int i;
	double z = 1.0;
	for (i = 0; i < n; i++)
	{
		z *= x;
	}
	return z;
}

long long frac(int n)
{
	static long long o = 1;
	o *= n;
	return o;
}

int main()
{
	double x;
	int n;
	scanf("%lf%d", &x, &n);
	printf("The result is %lf", sum(x, n));
	return 0;
}