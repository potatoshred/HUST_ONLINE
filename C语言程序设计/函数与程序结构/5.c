#include <stdio.h>

/**
  请使用递归定义此函数，将输入的一行字符逆序输出。
  字符的输入和输出用getchar和putchar函数
 **/
void myrever(void)
{
  /**********  Begin  **********/
  char tmp = getchar();
  if (tmp != '\n')
  {
    myrever();
    putchar(tmp);
  }
  /**********  End  **********/
}

// 请根据此主函数流程使用递归完成step5_stu.h文件中myrever()函数

int main(void)
{
  myrever();
  return 0;
}