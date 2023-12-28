#include<stdio.h>

void move(int arr[],int n,int k){
	/**********  Begin  **********/
	int tmp[100];
	for (int i = 0; i < k; i++)
	{
		tmp[i+n-k] = arr[i];
	}
	for (int i = 0; i < n-k; i++)
	{
		tmp[i] = arr[i+k];
	}
	for (int i = 0; i < n; i++)
	{
		arr[i] = tmp[i];
	}
	
    
	/**********  End  **********/
}
#include<stdio.h>
#define SIZE 100
void move(int arr[],int n,int k);
int main()
{
	int arr[SIZE];
    int n,i,k;
	scanf("%d", &n);
	for (i = 0; i < n; i++) {
		scanf("%d", &arr[i]);
	}
	scanf("%d",&k);
    
	move(arr,n,k);   // 交换
    
	for (i = 0; i < n; i++) {
		printf("%d ", arr[i]);
	}

	return 0;
}