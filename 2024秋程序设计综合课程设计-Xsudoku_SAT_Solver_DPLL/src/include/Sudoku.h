#pragma once

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Fisher-Yates 洗牌算法来随机打乱数组
void Shuffle(int arr[], int n)
{
    srand(time(0));
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
}

// 检查数字在该行是否合法
bool Conflict_Row(int board[9][9], int row, int num)
{
    for (int col = 0; col < 9; col++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 检查数字在该列是否合法
bool Conflict_Col(int board[9][9], int col, int num)
{
    for (int row = 0; row < 9; row++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 检查数字在该3x3宫格是否合法
bool Conflict_Block(int board[9][9], int startRow, int startCol, int num)
{
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[row + startRow][col + startCol] == num) {
                return true;
            }
        }
    }
    return false;
}

bool Conflict_Cross(int board[9][9], int row, int col, int num)
{
    if (row + col == 8) { // 反对角线
        for (int i_row = 0; i_row < 9; i_row++) {
            if (i_row == row) { // 跳过本行
                continue;
            }
            if (board[i_row][8 - i_row] == num) {
                return true;
            }
        }
        return false;
    } else if (row == col) { // 正对角线
        for (int i_row = 0; i_row < 9; i_row++) {
            if (i_row == row) { // 跳过本行
                continue;
            }
            if (board[i_row][i_row] == num) {
                return true;
            }
        }
        return false;
    } else { // 不在对角线
        return false;
    }
}

// 检查能否在指定位置放置数字
bool Fillable(int board[9][9], int row, int col, int num)
{
    return !Conflict_Row(board, row, num) &&
           !Conflict_Col(board, col, num) &&
           !Conflict_Cross(board, row, col, num) &&
           !Conflict_Block(board, row - row % 3, col - col % 3, num);
}

// 回溯法生成完整的数独
bool Fill_Board(int board[9][9], int row, int col)
{
    if (row == 9 - 1 && col == 9) {
        return true;
    }

    if (col == 9) {
        row++;
        col = 0;
    }

    if (board[row][col] != 0) {
        return Fill_Board(board, row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (Fillable(board, row, col, num)) {
            board[row][col] = num;

            if (Fill_Board(board, row, col + 1)) {
                return true;
            }

            board[row][col] = 0;
        }
    }
    return false;
}

// 初始化9x9空数独
void Init_Board(int board[9][9])
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            board[row][col] = 0;
        }
    }
}

// 随机挖洞
void Dig(int board[9][9], int num_holes)
{
    srand(time(0));
    for (int i = 0; i < num_holes;) {
        int row = rand() % 9;
        int col = rand() % 9;
        if (board[row][col] != 0) {
            board[row][col] = 0;
            i++;
        }
    }
}

// 打印数独
void print_board(int board[9][9])
{
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] == 0)
                printf(". ");
            else
                printf("%d ", board[row][col]);
        }
        printf("\n");
    }
}

void Generate_XSudoku_And_Answer(int board[9][9], int given, int board_answer[9][9])
{
    Init_Board(board_answer);

    // 第一行随机生成1-9的排列
    int first_row[9] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    Shuffle(first_row, 9);

    // 将随机排列的第一行填入数独
    for (int col = 0; col < 9; col++) {
        board_answer[0][col] = first_row[col];
    }

    // 使用回溯法生成剩余数独
    Fill_Board(board_answer, 0, 9);

    // 拷贝
    for(int row = 0; row < 9; row++) {
        for(int col = 0; col < 9; col++) {
            board[row][col] = board_answer[row][col];
        }
    }
    
    // 随机挖洞
    int num_holes = 9 * 9 - given; // 40个空位
    Dig(board, num_holes);

}
