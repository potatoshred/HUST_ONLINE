#include <stdio.h>
#include <string.h>

#define N 4 /*  ��ַ���С  */

struct web /*  ��Ʊ�ʾ��ַ�Ľṹ  */
{
	/**********  Begin  **********/
	char abbr[8];
	char name[32];
	char site[32];
	/**********   End   **********/
};

void sort(struct web webs[], int n)
{
	/**********  Begin  **********/
	struct web tmp;
	int flag = 1;
	while (flag)
	{
		flag = 0;

		for (int i = 0; i < n - 1; i++)
		{
			if (webs[i].abbr[0] > webs[i + 1].abbr[0])
			{
				tmp = webs[i];
				webs[i] = webs[i + 1];
				webs[i + 1] = tmp;
				flag = 1;
			}
		}
	}
	/**********   End   **********/
}
int main()
{
	/**********  Begin  **********/
	struct web w[N], *tmp;
	tmp = w;
	for (int i = 0; i < N; i++)
	{
		scanf("%s %s %s", &tmp->abbr, &tmp->name, &tmp->site);
		tmp++;
	}

	char search[8];
	;
	scanf("%s", &search);

	sort(w, N);
	tmp = w;
	for (int i = 0; i < N; i++)
	{
		printf("%s %s %s\n", tmp->abbr, tmp->name, tmp->site);
		tmp++;
	}

	int have_abbr = 0;
	for (int i = 0; i < N; i++)
	{
		if (!strcmp(w[i].abbr, search))
		{
			have_abbr = 1;
			printf("%s", w[i].site);
		}
	}
	if (!have_abbr)
	{
		printf("δ�ҵ���Ѱ����ַ");
	}

	/**********   End   **********/
	return 0;
}