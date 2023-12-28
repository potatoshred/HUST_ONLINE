#include <stdio.h>

int main(int argc, char const *argv[])
{

    char sentence[128];
    scanf("%[^\n]", sentence);
    int k;
    scanf("%d", &k);
    int cnt = 0;
    while (sentence[cnt] != '\0')
    {
        if (sentence[cnt] >= 'A' && sentence[cnt] <= 'Z')
        {
            sentence[cnt] = (sentence[cnt] - 65 + k - 1) % 26 + 65;
        }
        cnt++;
    }

    cnt /= 2;
    char tmp;
    for (int i = 0; i < cnt; i++)
    {
        tmp = sentence[i * 2];
        sentence[i * 2] = sentence[i * 2 + 1];
        sentence[i * 2 + 1] = tmp;
    }

    printf("%s", sentence);

    return 0;
}
