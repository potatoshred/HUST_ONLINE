
#include <stdio.h>

/*****请在下面补充函数 inArray、selectSort 和 outArray 的定义 *****/
void inArray(int arr[], int n)
{
	int input;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &input);
		arr[i] = input;
	}
}
void outArray(int arr[], int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr[i]);
	}
	printf("\n");
}
void selectSort(int arr[], int n)
{
	int max, max_index, tmp;
	for (int i = 0; i < n; i++)
	{
		max = arr[0];
		max_index=0;
		for (int j = 0; j < n-i; j++)
		{
			if (max<arr[j])
			{
				max_index = j;
				max = arr[j];
			}
		}
		tmp = arr[n-1-i];
		arr[n-1-i] = max;
		arr[max_index] = tmp;
	}
	
}


#define SIZE 100
void inArray(int arr[], int n);
void selectSort(int arr[], int n);
void outArray(int arr[], int n);
int main()
{
	/**********  Begin  **********/
	int arr[SIZE], n, i;
	scanf("%d", &n); // 输入元素个数

	inArray(arr, n); // 输入数组的n个元素

	selectSort(arr, n); //  对数组元素排序

	outArray(arr, n); // 输出数组的n个元素

	/**********  End  **********/
	return 0;
}
