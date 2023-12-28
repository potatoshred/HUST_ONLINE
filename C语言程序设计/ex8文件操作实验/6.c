/*
第6关：旋转图像3.(3)
任务描述
本关任务：利用文件操作重写实验六程序设计第(4)题。原始矩阵数据存放在当前目录下的文本文件matrix.in中，文件的第一行是两个整数n和m，表示矩阵的行数n和列数m，接下来的n行，每行有m个整数，表示矩阵数据。要求从matrix.in读数据，旋转后的矩阵输出到当前目录下的文本文件matrix.out中，该文件有m行，每行有n个整数。
   你不需要输出matrix.out中的内容，由平台输出。

编程要求
根据提示，在右侧编辑器补充代码。

测试说明
平台会对你编写的代码进行测试，并输出matrix.out中的内容：
测试输入：
matrix1.in
—— 预期输出 ——
—— 实际输出 ——

3 4
5 2
1 3


测试输入：
matrix2.in
—— 预期输出 ——
—— 实际输出 ——

4 8 12
3 7 11
2 6 10
1 5 9
*/
#include <stdio.h>
#include <stdlib.h>

int main()
{
   char path[32];
   scanf("%s", path);
   FILE *fp = fopen(path, "r");

   int row, column;
   fscanf(fp, "%d %d\n", &row, &column);

   int **table = (int **)malloc(row * sizeof(int *));

   for (int i = 0; i < row; i++)
   {
      table[i] = (int *)malloc(column * sizeof(int));
   }

   for (int i = 0; i < row; i++)
   {
      for (int j = 0; j < column; j++)
      {
         fscanf(fp, "%d", &table[i][j]);
      }
   }

   fclose(fp);

   fp = fopen("matrix.out", "w");

   for (int j = 0; j < column; j++)
   {
      fprintf(fp, "%d", table[0][column - 1 - j]);
      for (int i = 1; i < row; i++)
      {
         fprintf(fp, " %d", table[i][column - 1 - j]);
      }
      fputc('\n', fp);
   }

   fclose(fp);
   return 0;
}
