#include <stdio.h>
#include <math.h>

void conversion(char str[])
{
	/**********  Begin  **********/
	char c, tmp[100];
	int i = 0, j = 0;
	while (str[i])
	{
		c = str[i];
		if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
		{
			tmp[j] = c;
			j++;
		}else
		{
			break;
		}
		
		i++;
	}
	int result = 0;
	// printf("%d\n", j);
	for (int i = 0; i < j; i++)
	{
		c = tmp[i];
		if (c >= 'A' && c <= 'F')
		{
			result += (c - 55) * pow(16, j - i - 1);
		}
		else if (c >= 'a' && c <= 'f')
		{
			result += (c - 87) * pow(16, j - i - 1);

		}
		else
		{
			result += (c - 48) * pow(16, j - i - 1);
		}
	}
	printf("%d", result);
	/**********  End  **********/
}

#define SIZE 100
int main()
{
	/**********  Begin  **********/
	char str[100];
	scanf("%s", str);
	conversion(str);
	/**********  End  **********/
	return 0;
}
