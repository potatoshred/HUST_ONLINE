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
    // 检查坐标是否越界，以及是否是墙壁或已访问过的位置
    if (x >= 0 && x < ROWS && y >= 0 && y < COLS && maze[x][y] == 0 && visited[x][y] == 0) {
        return 1;
    }
    return 0;
}

int dfs(int x, int y, int destX, int destY) {
    if (x == destX && y == destY) {
        return 1; // 找到目标位置
    }

    visited[x][y] = 1; // 标记当前位置为已访问

    // 尝试四个方向的移动
    if (isSafe(x - 1, y) && dfs(x - 1, y, destX, destY)) {
        return 1; // 向上移动成功
    }
    if (isSafe(x + 1, y) && dfs(x + 1, y, destX, destY)) {
        return 1; // 向下移动成功
    }
    if (isSafe(x, y - 1) && dfs(x, y - 1, destX, destY)) {
        return 1; // 向左移动成功
    }
    if (isSafe(x, y + 1) && dfs(x, y + 1, destX, destY)) {
        return 1; // 向右移动成功
    }

    visited[x][y] = 0; // 恢复当前位置为未访问状态
    return 0; // 当前路径无法到达目标位置
}

int main() {
    int startX = 0; // 起始位置的坐标
    int startY = 0;
    int destX = 5; // 目标位置的坐标
    int destY = 5;

    if (dfs(startX, startY, destX, destY)) {
        printf("可以从起点到达终点。\n");
    } else {
        printf("无法从起点到达终点。\n");
    }

    return 0;
}