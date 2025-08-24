
#include "raylib.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Global.h"
#include "SAT.h"
#include "Sudoku.h"

#define SIZE 9
#define CELL_SIZE 50
#define PADDING 100      // 边界留白
#define DISC_RADIUS 60   // 数字选择圆盘半径
#define MAX_SCALE 1.5f   // 最大缩放比例
#define MIN_SCALE 0.5f   // 最小缩放比例
#define SCALE_SPEED 0.1f // 缩放速度

int selectedRow = -1;
int selectedCol = -1;
bool discVisible = false;
float discScale = MIN_SCALE; // 圆盘缩放比例

Rectangle rectButtonNew = {PADDING, 20, 100, 50};
Rectangle rectButtonSolve = {PADDING + 120, 20, 100, 50};
Rectangle rectButtonAns = {PADDING + 240, 20, 100, 50};
Rectangle rectButtonReset = {PADDING + 360, 20, 100, 50};
Rectangle rectButtonTLE = {PADDING, PADDING + CELL_SIZE *SIZE + 30, 100, 80};
Rectangle rectButtonSAT = {PADDING + 120, PADDING + CELL_SIZE *SIZE + 20, 200, 100};
Color colorButtonLoad = (Color){100, 200, 100, 255};

Vector2 mousePosition;
FilePathList droppedFiles;
char inputSudokuFilePath[256] = "";
int droppedFileCount = 0;

float easeInOut(float t, float start, float end)
{
    float div = 2.0;
    t /= (end - start) / div;
    if (t < 1) {
        return start + (end - start) / div * t * t * t;
    }
    t--;
    return start + (end - start) / div * (t * t * t + 2);
}

void UpdateBoardMask()
{
    IS_SAT = -1; // 重置状态
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] != 0) {
                board_mask[row][col] = 1;
            } else {
                board_mask[row][col] = 0;
            }
        }
    }
}

void AssignDragDropFiles()
{
    if (IsFileDropped()) {

        mousePosition = GetMousePosition();
        droppedFiles = LoadDroppedFiles();
        droppedFileCount = droppedFiles.count;

        if (droppedFileCount && CheckCollisionPointRec(mousePosition, rectButtonNew)) {
            colorButtonLoad = GREEN; // 高亮显示区域
            strcpy(inputSudokuFilePath, droppedFiles.paths[0]);

            is_sudoku = true;
            is_sudoku_gui = true;

            Read_Board_From_File(inputSudokuFilePath);
            UpdateBoardMask();
        }
        if (droppedFileCount && CheckCollisionPointRec(mousePosition, rectButtonSAT)) {

            strcpy(inputSudokuFilePath, droppedFiles.paths[0]);

            is_sudoku = false;
            is_sudoku_gui = true;
            printf("\nReading SAT problem from file %s\n", inputSudokuFilePath);

            Create_CNF_From_File(inputSudokuFilePath);
            Init_IntStack(&backtrack_stack); // 初始化回溯栈

            // 记录时间(全局变量)
            start_time = clock();
            // 处理初始单位子句，如果有的话
            Preprocess_Unit_Clause();
            // 执行主DPLL过程
            DPLL();
        }
        UnloadDroppedFiles(droppedFiles);
    }

    if (IS_SAT == true) {
        // DrawText("SAT", 0, 0, 32, BLACK);
        DrawText("SAT", PADDING + 360, PADDING + SIZE * CELL_SIZE + 40, 32, DARKGREEN);
        DrawText(TextFormat(" %d ms", elapse_time + 1), PADDING + 360, PADDING + SIZE * CELL_SIZE + 80, 20, DARKGREEN);
    } else if (IS_SAT == false) {
        DrawText("UNSAT", PADDING + 360, PADDING + SIZE * CELL_SIZE + 40, 32, RED);
        DrawText(TextFormat(" %d ms", elapse_time + 1), PADDING + 360, PADDING + SIZE * CELL_SIZE + 80, 20, RED);
    }
}

void DrawButton(Rectangle rect, Color color, const char *text)
{
    // DrawRectangleRec(rect, color);
    DrawRectangleLinesEx(rect, 4, color);
    DrawText(text, rect.x + rect.width / 2 - MeasureText(text, 20) / 2, rect.y + rect.height / 4, 20, BLACK);
}

void DrawBoard()
{
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {

            Rectangle cell = {PADDING + col * CELL_SIZE, PADDING + row * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            if (board_mask[row][col] == 1) { // 固有数字的格子
                DrawRectangleRec(cell, LIGHTGRAY);
            }
            if (board_mask[row][col] == 0 && board[row][col] != 0) { // 填入数字的格子

                int tmp = board[row][col]; // 临时变量
                board[row][col] = 0;

                if (Fillable(board, row, col, tmp)) {                    // 填入数字合法
                    DrawRectangleRec(cell, (Color){168, 233, 168, 255}); // 将该格子标记为绿色
                }
                board[row][col] = tmp;
            }
            if (selectedRow == row && selectedCol == col) {
                DrawRectangleRec(cell, (Color){0, 200, 255, 255});
            }
            DrawRectangleLines(cell.x, cell.y, cell.width, cell.height, BLACK);
        }
    }
}
void DrawConflict()
{
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {

            Rectangle cell = {PADDING + col * CELL_SIZE, PADDING + row * CELL_SIZE, CELL_SIZE, CELL_SIZE};

            if (board_mask[row][col] == 0 && board[row][col] != 0) { // 填入数字的格子

                int tmp = board[row][col]; // 临时变量
                board[row][col] = 0;

                if (!Fillable(board, row, col, tmp)) { // 冲突

                    if (Conflict_Row(board, row, tmp)) { // 行冲突
                        DrawLineEx((Vector2){PADDING, PADDING + (row + 0.5) * CELL_SIZE},
                                   (Vector2){
                                       PADDING + SIZE * CELL_SIZE,
                                       PADDING + (row + 0.5) * CELL_SIZE,
                                   },
                                   4, RED);
                    }

                    if (Conflict_Col(board, col, tmp)) { // 列冲突
                        DrawLineEx((Vector2){PADDING + (col + 0.5) * CELL_SIZE, PADDING},
                                   (Vector2){PADDING + (col + 0.5) * CELL_SIZE, PADDING + CELL_SIZE * SIZE},
                                   4, RED);
                    }

                    if (Conflict_Block(board, row - row % 3, col - col % 3, tmp)) { // 3x3块冲突
                        // 3x3边界描红
                        // printf("block conflict @ %d,%d,%d\n", row, col, tmp);
                        DrawRectangleLinesEx((Rectangle){PADDING + (col / 3) * 3 * CELL_SIZE,
                                                         PADDING + (row / 3) * 3 * CELL_SIZE,
                                                         3 * CELL_SIZE,
                                                         3 * CELL_SIZE},
                                             5, RED);
                    }

                    char c = Conflict_Cross(board, row, col, tmp);
                    if (c && c == '/') { // 对角线冲突
                        // 绘制对角线
                        DrawLineEx((Vector2){PADDING + SIZE * CELL_SIZE, PADDING},
                                   (Vector2){PADDING, PADDING + SIZE * CELL_SIZE},
                                   4, RED);
                    }
                    if (c && c == '\\') { // 反对角线冲突
                        // 绘制反对角线
                        DrawLineEx((Vector2){PADDING, PADDING},
                                   (Vector2){PADDING + SIZE * CELL_SIZE, PADDING + SIZE * CELL_SIZE},
                                   4, RED);
                    }
                    DrawRectangleRec(cell, (Color){255, 100, 100, 255}); // 将该格子标记为红色
                }
                board[row][col] = tmp;
            }
            if (board[row][col] != 0) {
                DrawText(TextFormat("%d", board[row][col]),
                         cell.x + CELL_SIZE / 4,
                         cell.y + CELL_SIZE / 4,
                         32, BLACK);
            }
        }
    }
    for (int i = 1; i < 3; i++) {
        int linePosition = PADDING + i * CELL_SIZE * 3;
        DrawLineEx((Vector2){PADDING, linePosition}, (Vector2){PADDING + SIZE * CELL_SIZE, linePosition}, 5.0f, BLACK);
        DrawLineEx((Vector2){linePosition, PADDING}, (Vector2){linePosition, PADDING + SIZE * CELL_SIZE}, 5.0f, BLACK);
    }
}
void UpdateSelection()
{

    if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        mousePosition = GetMousePosition();
        // 判断鼠标是否在棋盘区域内
        if (mousePosition.x > PADDING && mousePosition.x < PADDING + SIZE * CELL_SIZE && mousePosition.y > PADDING && mousePosition.y < PADDING + SIZE * CELL_SIZE) {
            selectedCol = (mousePosition.x - PADDING) / CELL_SIZE;
            selectedRow = (mousePosition.y - PADDING) / CELL_SIZE;

            if (selectedRow < SIZE && selectedCol < SIZE && board_mask[selectedRow][selectedCol] == 0) {
                discVisible = true;    // 显示数字选择圆盘
                discScale = MIN_SCALE; // 重置缩放比例
            } else {
                selectedRow = -1;
                selectedCol = -1;
                discVisible = false;
            }
        } else if (CheckCollisionPointRec(mousePosition, rectButtonNew)) {
            // 点击“新游戏”按钮
            is_sudoku = true;
            Generate_XSudoku_And_Answer(board, board_given, board_ans);
            UpdateBoardMask();
        } else if (CheckCollisionPointRec(mousePosition, rectButtonSolve)) {
            colorButtonLoad = (Color){100, 200, 100, 255}; // 高亮显示区域
            is_sudoku_gui = true;
            UpdateBoardMask();
            Board_To_CNF(board, "sudoku.cnf");
            Create_CNF_From_File("sudoku.cnf");
            Init_IntStack(&backtrack_stack); // 初始化回溯栈

            // 记录时间(全局变量)
            start_time = clock();
            // 处理初始单位子句，如果有的话
            Preprocess_Unit_Clause();
            // 执行主DPLL过程
            DPLL();
        } else if (CheckCollisionPointRec(mousePosition, rectButtonAns)) {
            // 点击“答案”按钮
            // 显示答案
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    board[row][col] = board_ans[row][col];
                }
            }
        } else if (CheckCollisionPointRec(mousePosition, rectButtonReset)) {
            // 点击“重置”按钮
            for (int row = 0; row < SIZE; row++) {
                for (int col = 0; col < SIZE; col++) {
                    if (board_mask[row][col] == 0) {
                        board[row][col] = 0;
                    }
                }
            }
        } else if (CheckCollisionPointRec(mousePosition, rectButtonTLE)) {
            enableTLE = !enableTLE;
        }
    }
}

void DrawDisc(int centerX, int centerY)
{
    for (int num = 0; num <= 9; num++) {
        int angle = num * (360 / 10) - 90;
        int x = centerX + (DISC_RADIUS * discScale) * cosf(angle * (PI / 180));
        int y = centerY + (DISC_RADIUS * discScale) * sinf(angle * (PI / 180));

        Color color = (num % 2 == 0) ? (Color){173, 216, 230, 255} : (Color){220, 228, 235, 255};
        DrawCircle(x, y, 20 * discScale, color); // 绘制色块
        if (num!=0)
            DrawText(TextFormat("%d", num), x - 10 * discScale, y - 10 * discScale, 20 * discScale, BLACK);
    }
}

void UpdateInput()
{
    if (discVisible) {
        Vector2 mousePosition = GetMousePosition();
        for (int num = 0; num <= 9; num++) {
            int angle = num * (360 / 10) - 90;
            int x = PADDING + (selectedCol * CELL_SIZE) + (CELL_SIZE / 2) + (DISC_RADIUS * discScale) * cosf(angle * (PI / 180));
            int y = PADDING + (selectedRow * CELL_SIZE) + (CELL_SIZE / 2) + (DISC_RADIUS * discScale) * sinf(angle * (PI / 180));

            if (CheckCollisionPointCircle(mousePosition, (Vector2){x, y}, 20 * discScale)) {
                if (IsMouseButtonPressed(MOUSE_RIGHT_BUTTON)) {
                    board[selectedRow][selectedCol] = num;
                    discVisible = false; // 选择后隐藏圆盘
                    selectedRow = -1;
                    selectedCol = -1;
                }
            }
        }
    }
}

void UpdateAnimation()
{
    if (discVisible && discScale < MAX_SCALE) {
        discScale += SCALE_SPEED; // 增加缩放比例
        // discScale = easeInOut(discScale, MIN_SCALE, MAX_SCALE); // 缓动效果
        if (discScale > MAX_SCALE) {
            discScale = MAX_SCALE; // 限制最大缩放比例
        }
    } else if (!discVisible && discScale > MIN_SCALE) {
        discScale -= SCALE_SPEED; // 减少缩放比例
        if (discScale < MIN_SCALE) {
            discScale = MIN_SCALE; // 限制最小缩放比例
        }
    }
}

int main(void)
{
    // 调整窗口大小
    InitWindow(640, 700, "Sudoku Game");
    SetTargetFPS(60);

    is_sudoku = true;
    Generate_XSudoku_And_Answer(board, board_given, board_ans);
    UpdateBoardMask();

    while (!WindowShouldClose()) {
        AssignDragDropFiles();

        UpdateInput();
        UpdateAnimation(); // 更新动画

        BeginDrawing();
        ClearBackground(RAYWHITE);
        UpdateSelection();

        DrawButton(rectButtonNew, (Color){100, 200, 255, 255}, "NEW");
        DrawButton(rectButtonTLE, enableTLE?(Color){100, 200, 255, 255}:(Color){255, 255, 255, 255}, enableTLE?"enable\n\ntimeout":"disable\n\ntimeout");
        DrawButton(rectButtonSolve, colorButtonLoad, "Solve");
        DrawButton(rectButtonAns, (Color){100, 100, 255, 255}, "ANSWER");
        DrawButton(rectButtonReset, BLACK, "RESET");
        DrawButton(rectButtonSAT, (Color){100, 200, 255, 255}, "SAT SOLVER\n\n(drop .cnf here)");

        DrawBoard();
        DrawConflict();
        if (discVisible) {
            // 计算圆盘中心位置
            int centerX = PADDING + (selectedCol * CELL_SIZE) + (CELL_SIZE / 2);
            int centerY = PADDING + (selectedRow * CELL_SIZE) + (CELL_SIZE / 2);

            DrawDisc(centerX, centerY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}