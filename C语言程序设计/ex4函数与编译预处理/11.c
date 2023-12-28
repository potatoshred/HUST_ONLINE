/*
第11关：多文件C程序

任务描述
实验课本 实验4 程序设计第（6）题
本关任务：一个C程序由file1.c、file2.c、file.h三个文件组成，两个源文件的内容已经给出。试编辑该多文件C程序，补充file.h头文件内容，相应修改file1.c、file2.c。平台评测时会自动将file1.c、file2.c进行编译、链接成可执行文件并运行。

提示：可依据下图提示进行文件切换，完成多文件的编辑。
 a 

相关知识
（1）C程序的多文件结构；（2）外部变量的定义与声明；（3）函数的定义与声明。

测试说明
平台会对你编写的代码进行测试：

测试输入：q
预期输出：
in file1 x=10,y=20,ch is q
in file2 x=11,y=21,ch is r

测试输入：a
预期输出：
in file1 x=10,y=20,ch is a
in file2 x=11,y=21,ch is b
*/
#include<stdio.h>
int x,y;
char ch;
int main(void)
{
	x=10;
   y=20;
   ch=getchar();
   printf("in file1 x=%d,y=%d,ch is %c\n",x,y,ch);
	func1();
	return 0;
}