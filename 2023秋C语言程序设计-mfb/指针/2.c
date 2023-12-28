#include <stdio.h>
// 函数的输入为 int类型数组 和数组长度
void reverseOrder(int a[], int n)
{
    // 请在此处编辑您的代码
    /**********  Begin  **********/
    int tmp, i = n >> 1;
    while (i)
    {
        tmp = *(a + i - 1);
        *(a + i - 1) = *(a + n - i);
        *(a + n - i) = tmp;
        i--;
    }

    /**********  End  **********/
}
#define SIZE 100

int main()
{
    /**********  Begin  **********/
    int n, i;
    int arr[SIZE];
    scanf("%d", &n);
    for (i = 0; i < n; i++)
    {
        scanf("%d", &arr[i]);
    }

    reverseOrder(arr, n);

    for (i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }

    /**********  End  **********/
    return 0;
}
