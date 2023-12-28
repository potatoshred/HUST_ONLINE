#include <stdio.h>
// 冒泡升序排序 ，程序的输入为 int类型数组 和数组长度
// 请在此处编辑您的代码
/**********  Begin  **********/
void bubble_sort(int *a, int n)
{
    int flag = 1, i = n, tmp;
    while (flag)
    {
        flag = 0;
        for (int j = 0; j < i - 1; j++)
        {
            if (*(a + j + 1) < *(a + j))
            {
                tmp = *(a + j);
                *(a + j) = *(a + j + 1);
                *(a + j + 1) = tmp;
                flag = 1;
            }
        }
        i--;
    }
}
/**********  End  **********/
#define SIZE 100
#define N 10
void bubble_sort(int *a, int n);
int main()
{
    /**********  Begin  **********/
    int a[SIZE], i, k;
    for (i = 0; i < N; i++)
    {
        scanf("%d", &a[i]);
    }
    bubble_sort(a, N);
    for (k = 0; k < N; k++)
    {
        printf("%d ", a[k]);
    }
    /**********   End   **********/
    return 0;
}
