#include <stdlib.h>
#include <stdio.h>
void diceGame(int randSeed)
{
    srand((unsigned)randSeed);
    int a, b, score, round = 1;
    a = rand() % 6 + 1;
    b = rand() % 6 + 1;
    score = a + b;
    printf("Round %d:  Score:%d  ", round, score);

    if (score == 7 || score == 11)
    {
        printf("Success!\n");
        return ;
    }
    else if (score == 2 || score == 3 || score == 12)
    {
        printf("Failed!\n");
        return ;
    }
    else
    {
        printf("Continue!\n");
    }
    printf("Next rounds: Score %d:Success, Score 7:Failed, others:Continue\n", score);
    int tmp = score;
    while (1)
    {
        round++;
        a = rand() % 6 + 1;
        b = rand() % 6 + 1;
        score = a + b;
        printf("Round %d:  Score:%d  ", round, score);
        if (score == tmp)
        {
            printf("Success!\n");
            return ;
        }

        else if (score == 7)
        {
            printf("Failed!\n");
            return ;
        }
        else
        {
            printf("Continue!\n");
        }
    }
}
int main()
{
    int randSeed;
    scanf("%d", &randSeed); // 输入整数作为随机数种子
    diceGame(randSeed);
    return 0;
}