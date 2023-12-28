#include <stdio.h>

#define ROWS 6
#define COLS 6

int maze[ROWS][COLS] = {
    {0, 1, 0, 0, 0, 0},
    {0, 1, 0, 1, 1, 0},
    {0, 0, 0, 1, 0, 0},
    {0, 1, 1, 1, 0, 1},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

int visited[ROWS][COLS] = {0};

int isSafe(int x, int y) {
    // ��������Ƿ�Խ�磬�Լ��Ƿ���ǽ�ڻ��ѷ��ʹ���λ��
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && visited[x][y] == 0) {
        return 1;
    }
    return 0;
}

int dfs(int x, int y, int destX, int destY) {
    if (x == destX && y == destY) {
        return 1; // �ҵ�Ŀ��λ��
    }

    visited[x][y] = 1; // ��ǵ�ǰλ��Ϊ�ѷ���

    // �����ĸ�������ƶ�
    if (isSafe(x - 1, y) && dfs(x - 1, y, destX, destY)) {
        return 1; // �����ƶ��ɹ�
    }
    if (isSafe(x + 1, y) && dfs(x + 1, y, destX, destY)) {
        return 1; // �����ƶ��ɹ�
    }
    if (isSafe(x, y - 1) && dfs(x, y - 1, destX, destY)) {
        return 1; // �����ƶ��ɹ�
    }
    if (isSafe(x, y + 1) && dfs(x, y + 1, destX, destY)) {
        return 1; // �����ƶ��ɹ�
    }

    visited[x][y] = 0; // �ָ���ǰλ��Ϊδ����״̬
    return 0; // ��ǰ·���޷�����Ŀ��λ��
}

int main() {
    int startX = 0; // ��ʼλ�õ�����
    int startY = 0;
    int destX = 5; // Ŀ��λ�õ�����
    int destY = 5;

    if (dfs(startX, startY, destX, destY)) {
        printf("���Դ���㵽���յ㡣\n");
    } else {
        printf("�޷�����㵽���յ㡣\n");
    }

    return 0;
}