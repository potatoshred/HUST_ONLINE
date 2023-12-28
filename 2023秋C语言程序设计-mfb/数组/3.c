#include<stdio.h>

int main()
{
	/**********  Begin  **********/
	char table[128] = {0};
	char c;
	int others = 0;
	while ((c=getchar())!='\n')	
	{
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		{
			if (c >= 'a' && c <= 'z')
			{
				c-=32;
			}
			
			table[c]++;
		}else{
			others++;
		}
	}
	for (int i = 0; i < 128; i++)
	{
		if (table[i])
		{
			printf("%c:%d\n",i, table[i]);
		}
		
	}
	printf("others:%d", others);
	
	/**********  End  **********/
	return 0; 
}
