#pragma once

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#ifdef _WIN32
#include <direct.h> // For _getcwd on Windows
#define getcwd _getcwd
#else
#include <unistd.h> // For getcwd on POSIX systems
#endif
#include "Global.h"

/**
 * @brief 取正
 * @param literal 字面
 * @return int 正值
 */
int Abs(int literal)
{
    return (literal > 0) ? literal : -literal;
}

/**
 * @brief 从cnf文件创建子句集
 * @param filename 文件名
 * @return void
 */
void Create_CNF_From_File(const char *filename)
{
    // 打开文件
    FILE *cnf = fopen(filename, "r");
    // 跳过注释行
    char c = fgetc(cnf);
    while (c == 'c') {
        while (c != '\n')
            c = fgetc(cnf);
        c = fgetc(cnf);
    }

    // p行 "cnf num_vars num_clauses"
    char _cnf[4]; // 临时变量
    fscanf(cnf, "%s %d %d", _cnf, &num_vars, &num_clauses);

    clauses = (IntVector *)malloc(num_clauses * sizeof(IntVector));  // 根据子句数量，指定子句集大小
    clause_mask = (int *)calloc(num_clauses, sizeof(int));           // 子句确定标志初始化为0
    num_undef_each_clause = (int *)calloc(num_clauses, sizeof(int)); // 子句中未确定变量的数量初始化为0
    for (int i = 0; i < num_clauses; ++i) {
        Init_IntVector(&clauses[i]); // 初始化子句
    }

    // 根据变元数量初始化大小
    clauses_contain_positive = (IntVector *)malloc((num_vars + 1) * sizeof(IntVector));
    clauses_contain_negative = (IntVector *)malloc((num_vars + 1) * sizeof(IntVector));
    for (int i = 1; i <= num_vars; ++i) {
        Init_IntVector(&clauses_contain_positive[i]);
        Init_IntVector(&clauses_contain_negative[i]);
    }

    // 创建子句集
    for (int clause = 0; clause < num_clauses; ++clause) {
        int literal;
        while (fscanf(cnf, "%d", &literal) && literal != 0) { // 读取子句中的字面，直到遇到0
            // 将字面加入所在子句
            push_back_IntVector(&clauses[clause], literal);

            // 记录每个正负字面出现的子句
            if (literal > 0) {
                push_back_IntVector(&clauses_contain_positive[Abs(literal)], clause);
            } else {
                push_back_IntVector(&clauses_contain_negative[Abs(literal)], clause);
            }
        }
        num_undef_each_clause[clause] = clauses[clause].size; // 记录每个子句中未确定变量的数量
    }

    model = (int *)malloc((num_vars + 1) * sizeof(int)); // 变量初始化为未确定
    for (int i = 1; i <= num_vars; ++i) {
        model[i] = UNDEFINED;
    }

    idx_next_literal = 0; // 初始化指向下一个从堆栈中传播的字面
    decision_level = 0;   // 初始化决策等级

    // 初始化活动计数器
    positive_literal_weights = (double *)malloc((num_vars + 1) * sizeof(double));
    negative_literal_weights = (double *)malloc((num_vars + 1) * sizeof(double));
    for (int i = 1; i <= num_vars; ++i) {
        positive_literal_weights[i] = 0.0;
        negative_literal_weights[i] = 0.0;
    }
    conflicts = 0;
}

/**
 * @brief 判断当前model下该literal真假
 * @param literal 字面
 * @return bool 真假
 */
int Eval_Literal(int literal)
{
    if (literal > 0) {
        return model[Abs(literal)];
    } else {
        if (model[Abs(literal)] == UNDEFINED) {
            return UNDEFINED;
        } else {
            return (model[Abs(literal)] == FALSE) ? TRUE : FALSE;
        }
    }
}

/**
 * @brief 将该literal确定为真，并压入回溯栈。若为数独环境，则还会将该字面所在行、列、块、对角线的候选值设为FALSE
 * @param literal 字面
 * @return void
 */
void Correct_Literal(int literal)
{
    push_IntStack(&backtrack_stack, literal);
    // debug
    // int a, b, c;
    // printf("CorrectLiteral: %04d\n", Literal_To_IJK(literal, &a, &b, &c));
    // printf("%16s", "Preprocess: ");
    // debug_IntStack(&backtrack_stack);
    model[Abs(literal)] = (literal > 0) ? TRUE : FALSE;

    bool is_push = true;
    Update_Mask(literal, is_push);

    // 如果是数独，且可确定一个格子(literal>0)，则可更新行、列、块的候选值
    // 所在行、列、块、对角线对应的相同值为FALSE
    // 自身的其他值为FALSE
    if (is_sudoku && literal > 0) {
        // 所在行、列
        int row;
        int col;
        int num;
        Literal_To_IJK(literal, &row, &col, &num);

        // 排除Cell其他候选值
        for (int i = 1; i <= 9; i++) {
            if (i == num) { // 跳过本身
                continue;
            }
            int literal_tmp = IJK_To_Literal(row, col, i);
            if (model[Abs(literal_tmp)] == UNDEFINED) {
                Correct_Literal(-literal_tmp);
            } else if (Eval_Literal(literal_tmp) == TRUE) {
                if (is_sudoku_gui) {
                    return Exit_With_Stat(false);
                } else {
                    Exit_With_Stat(false);
                }
            }
        }

        // 排除所在行
        for (int i = 0; i < 9; i++) {
            if (i == col) { // 跳过本身
                continue;
            }
            int literal_tmp = IJK_To_Literal(row, i, num);
            if (model[Abs(literal_tmp)] == UNDEFINED) {
                Correct_Literal(-literal_tmp);
            } else if (Eval_Literal(literal_tmp) == TRUE) {
                if (is_sudoku_gui) {
                    return Exit_With_Stat(false);
                } else {
                    Exit_With_Stat(false);
                }
            }
        }
        // 排除所在列
        for (int i = 0; i < 9; i++) {
            if (i == row) { // 跳过本身
                continue;
            }
            int literal_tmp = IJK_To_Literal(i, col, num);
            if (model[Abs(literal_tmp)] == UNDEFINED) {
                Correct_Literal(-literal_tmp);
            } else if (Eval_Literal(literal_tmp) == TRUE) {
                if (is_sudoku_gui) {
                    return Exit_With_Stat(false);
                } else {
                    Exit_With_Stat(false);
                }
            }
        }
        // 排除所在块
        int block_row = row / 3;
        int block_col = col / 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                int literal_tmp = IJK_To_Literal(i + block_row * 3, j + block_col * 3, num);
                if (literal == literal_tmp) {
                    continue;
                }
                if (model[Abs(literal_tmp)] == UNDEFINED) {
                    Correct_Literal(-literal_tmp);
                } else if (Eval_Literal(literal_tmp) == TRUE) {
                    if (is_sudoku_gui) {
                        return Exit_With_Stat(false);
                    } else {
                        Exit_With_Stat(false);
                    }
                }
            }
        }
        // 排除所在对角线
        if (row == col) {
            for (int i = 0; i < 9; i++) {
                if (i == row) { // 跳过本身
                    continue;
                }
                int literal_tmp = IJK_To_Literal(i, i, num);
                if (model[Abs(literal_tmp)] == UNDEFINED) {
                    Correct_Literal(-literal_tmp);
                } else if (Eval_Literal(literal_tmp) == TRUE) {
                    if (is_sudoku_gui) {
                        return Exit_With_Stat(false);
                    } else {
                        Exit_With_Stat(false);
                    }
                }
            }
        }
        if (col + row == 8) {
            for (int i = 0; i < 9; i++) {
                if (i == row) { // 跳过本身
                    continue;
                }
                int literal_tmp = IJK_To_Literal(i, 8 - i, num);
                if (model[Abs(literal_tmp)] == UNDEFINED) {
                    Correct_Literal(-literal_tmp);
                } else if (Eval_Literal(literal_tmp) == TRUE) {
                    if (is_sudoku_gui) {
                        return Exit_With_Stat(false);
                    } else {
                        Exit_With_Stat(false);
                    }
                }
            }
        }
    }
}

/**
 * @brief 更新冲突的子句中的字面对应的权重
 * @return void
 */
void Update_Weights(IntVector clause)
{
    conflicts++;
    if (conflicts % Weight_Update == 0) {
        for (int i = 1; i <= num_vars; i++) {
            {
                positive_literal_weights[i] /= 2.0;
                negative_literal_weights[i] /= 2.0;
            }
        }

        for (int i = 0; i < clause.size; i++) {
            int literal = clause.data[i];
            if (literal > 0) {
                positive_literal_weights[Abs(literal)] += Weight_Increment;
            } else {
                negative_literal_weights[Abs(literal)] += Weight_Increment;
            }
        }
    }
}

void Update_Mask(int literal, bool is_push)
{

    for (int i = 0; i < clauses_contain_positive[Abs(literal)].size; i++) {
        int clause = clauses_contain_positive[Abs(literal)].data[i];
        num_undef_each_clause[clause] -= is_push ? 1 : -1;
        if (literal > 0) {
            clause_mask[clause] += is_push ? 1 : -1;
        }
    }
    for (int i = 0; i < clauses_contain_negative[Abs(literal)].size; i++) {
        int clause = clauses_contain_negative[Abs(literal)].data[i];
        num_undef_each_clause[clause] -= is_push ? 1 : -1;
        if (literal < 0) {
            clause_mask[clause] += is_push ? 1 : -1;
        }
    }
}

void Exit_With_Stat(bool is_sat)
{
    end_time = clock();
    elapse_time = (int)(end_time - start_time) * 1000 / CLOCKS_PER_SEC;

    IS_SAT = is_sat;
    
    if (is_sat) {

        if (is_sudoku) {
            Answer_Board();
        }
        Verify();
    }

    printf("Exporting Solution File...\n");
    if (is_sat) {
        printf("s 1\nv");
        for (int i = 1; i <= num_vars; ++i) {
            printf(" %d", (model[i] ? i : -i));
        }

    } else {
        printf("s 0\nv");
    }
    printf("\nt %d\n", elapse_time);

    Export_Solution_Res_File(is_sat);

    if (!is_sudoku_gui) {
        exit(0);
    }
}

int Get_Next_Decision_Literal()
{
    // 遍历找到最活跃的字面（无论正/负）
    double max_weight = 0.0;
    int max_weight_literal = 0;
    for (int i = 1; i <= num_vars; ++i) {
        // 仅处理未确定变量
        if (model[i] == UNDEFINED) {
            if (positive_literal_weights[i] >= max_weight) {
                max_weight = positive_literal_weights[i];
                max_weight_literal = i;
            }
            if (negative_literal_weights[i] >= max_weight) {
                max_weight = negative_literal_weights[i];
                max_weight_literal = -i;
            }
        }
    }
    // 返回最活跃的变量，或如果没有未确定变量，则返回0
    return max_weight_literal;
}

void Verify()
{
    for (int i = 0; i < num_clauses; i++) {
        bool exist_true_literal = false; // 子句中是否存在真字面，如果存在，则该子句为真，停止遍历
        for (int j = 0; !exist_true_literal && j < clauses[i].size; ++j) {
            exist_true_literal = (Eval_Literal(clauses[i].data[j]) == TRUE);
        }
        // 如果子句中不存在真字面，则该子句为假，则子句集UNSAT，model不成立
        if (!exist_true_literal) {
            printf("SAT Verification Failed! The last clause is:\n");
            for (int j = 0; j < clauses[i].size; j++) {
                printf("%d ", clauses[i].data[j]);
            }
            printf("\n");
            exit(1);
        }
    }
}

bool IsPropagateToConflict()
{
    while (idx_next_literal <= backtrack_stack.top) {
        int literal_p = backtrack_stack.data[idx_next_literal];
        idx_next_literal++; // 记录下一次字面的位置

        IntVector clauses_p = (literal_p > 0) ? clauses_contain_negative[Abs(literal_p)] : clauses_contain_positive[Abs(literal_p)];

        // 遍历当前字面为假时，所在的每个仍需判断的子句，看看能不能找到单子句
        for (int i_clause = 0; i_clause < clauses_p.size; i_clause++) {

            // 跳过已确定子句
            if (clause_mask[clauses_p.data[i_clause]] != 0) {
                continue;
            }

            IntVector clause = clauses[clauses_p.data[i_clause]];

            if (num_undef_each_clause[clauses_p.data[i_clause]] == 0) {        // 如果不存在真字面，且未确定字面数为0
                Update_Weights(clause);                                        // 此句不成立，更新子句中的字面对应的活动计数器
                return true;                                                   // 冲突，需要回溯，重新决策
            } else if (num_undef_each_clause[clauses_p.data[i_clause]] == 1) { // 如果不存在真字面，且未确定字面数为1
                int trustworthy_literal = 0;                                   // 记录最后一个未确定字面

                // 遍历子句每个字面，判断是否存在真字面，记录未确定字面数和最后一个未确定字面
                for (int i_literal = 0; i_literal < clause.size; ++i_literal) {
                    int value = Eval_Literal(clause.data[i_literal]); // 取出字面的值
                    if (value == UNDEFINED) {                         // 如果存在某个字面未确定
                        trustworthy_literal = clause.data[i_literal]; // 记录最后一个未确定字面
                    }
                } // end of 遍历子句字面
                Correct_Literal(trustworthy_literal); // 其余字面均为假，则将此唯一的未确定字面设为真，压入栈中
            }
        } // end of 遍历当前字面为假时，所在的每个仍需判断的子句
    }

    return false; // 栈中字面均已处理，无冲突
}

void DPLL()
{
    while (true) { // 模拟递归调用， 用回溯栈记录决策路径，
        // debug
        // printf("%16s", "next: ");
        // debug_IntStack(&backtrack_stack);

        while (IsPropagateToConflict()) { // conflict-driven back jumping

            // // debug
            // printf("%16s", "conflict: ");
            // debug_IntStack(&backtrack_stack);

            if (decision_level == 0) { // 如果未作任何决策就遇到冲突，，
                if (is_sudoku_gui) {
                    return Exit_With_Stat(false); // 则证明UNSAT，退出
                } else {
                    Exit_With_Stat(false); // 则证明UNSAT，退出}
                }
            }

            // 回溯到DECISION_MARK
            int literal = 0;
            while (peek_IntStack(&backtrack_stack) != DECISION_MARK) {
                literal = peek_IntStack(&backtrack_stack); // 取出栈顶字面
                model[Abs(literal)] = UNDEFINED;           // 回溯时，将字面设为未确定
                pop_IntStack(&backtrack_stack);            // 回溯栈弹出字面

                bool is_push = false;
                Update_Mask(literal, is_push); // 更新子句确定标志
            }

            pop_IntStack(&backtrack_stack);         // 弹出DECISION_MARK
            decision_level--;                       // 决策等级-1
            Correct_Literal(-literal);              // DECISION_MARK后的第一个字面反转
            idx_next_literal = backtrack_stack.top; // 指向回溯栈顶的该字面

            // 此时，该字面的决策反转，且不加DECISION_MARK，
            // 后续，根据此次决策。更新可确定的新的字面到栈中，每次压入都会重新检测是否有冲突
            // 若出现冲突，则代表该字面无论真假都会导致冲突，则需要回溯到更早的DECISION_MARK
            // 若不会冲突，则代表可以做新的决策

            // debug
            // printf("%16s", "backtrack: ");
            // debug_IntStack(&backtrack_stack);

        } // end of conflict-driven back jumping

        // 当前model没有冲突，则进行下一层决策
        int literal_next = Get_Next_Decision_Literal(); // 分裂策略

        if (literal_next == 0) { // 如此，则代表所有字面均为已确定
            // Exit_With_Stat(true);
            // 解找到，退出
            if (is_sudoku_gui) {
                return Exit_With_Stat(true);
            } else {
                Exit_With_Stat(true);
            }
        }

        decision_level++; // 决策等级+1
        idx_next_literal++;
        push_IntStack(&backtrack_stack, DECISION_MARK);
        Correct_Literal(literal_next); // 将字面设为真
    }
}

void Preprocess_Unit_Clause()
{
    for (int i = 0; i < num_clauses; i++) {
        if (clauses[i].size == 1) {
            int unit_literal = clauses[i].data[0];
            if (Eval_Literal(unit_literal) == UNDEFINED) {    // 该字面未确定
                Correct_Literal(unit_literal);                // 将字面设为真
            } else if (Eval_Literal(unit_literal) == FALSE) { // 说明出现过相反的单子句
                if (is_sudoku_gui) {
                    return Exit_With_Stat(false);
                } else {
                    Exit_With_Stat(false);
                }
            }
        }
    }
}

int IJK_To_Literal(int row, int col, int num)
{
    // row~[0, 8], col~[0, 8], num~[1, 9]
    if (num > 0)
        return (row * 9 + col) * 9 + num;
    else
        return -(row * 9 + col) * 9 + num;
}

int Literal_To_IJK(int literal, int *row, int *col, int *num)
{
    bool is_positive = (literal > 0);
    literal = Abs(literal); // 确保使用正字面
    *num = (literal % 9 == 0) ? 9 : literal % 9;
    int idx = (literal - *num) / 9;
    *col = idx % 9;
    *row = idx / 9;
    if (!is_positive) {
        *num = -*num;
    }
    int ret = *row * 100 + *col * 10 + Abs(*num);
    ret = (is_positive) ? ret : -ret;
    return ret;
}

int Eval_Cell(int row, int col)
{
    for (int num = 1; num <= 9; num++) {
        if (model[(row * 9 + col) * 9 + num] == TRUE) {
            return num;
        }
    }
    return 0;
}

void Fprint_Cell(FILE *fp, int row, int col, int num)
{
    fprintf(fp, "%d ", IJK_To_Literal(row, col, num));
}

void Read_Board_From_String(char *str)
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            char c = str[i * 9 + j];
            if (c >= '1' && c <= '9') {
                board[i][j] = str[i * 9 + j] - '0';
            }
        }
    }
}

void Read_Board_From_File(const char *filename)
{
    for(int i = 0; i < 9; i++) {
        for(int j = 0; j < 9; j++) {
            board[i][j] = 0;
        }
    }

    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", filename);
        exit(1);
    }
    char str[100];
    fgets(str, 100, fp);
    fclose(fp);
    if (strlen(str) == 81 || strlen(str) == 82) {
        Read_Board_From_String(str);
    } else {
        printf("Error: invalid sudoku layout\n");
        exit(1);
    }
}

void Board_To_CNF(int board[9][9], const char *out_filename)
{
    FILE *fp = fopen(out_filename, "w");
    if (fp == NULL) {
        printf("Error: cannot open file %s\n", out_filename);
        exit(1);
    }
    // 预留一行p
    fprintf(fp, "p cnf 729         ");
    int num_lines = 0;

    // 约束1：对于确定格子，转为单子句；对于未确定格子，可取值1-9，转为子句，子句数：9*9
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            if (board[row][col] != 0) { // 该格已有值，则将其作为确定单子句
                Fprint_Cell(fp, row, col, board[row][col]);
                fprintf(fp, "0\n");
            } else { // 该格未有值，则可以取任意值
                for (int num = 1; num <= 9; num++) {
                    Fprint_Cell(fp, row, col, num);
                }
                fprintf(fp, "0\n");
            }
            num_lines++;
        }
    }

    // 约束2：对于每格，不能有多个值，子句数：9*9*36
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            for (int num1 = 1; num1 <= 9; num1++) {
                for (int num2 = num1 + 1; num2 <= 9; num2++) {
                    Fprint_Cell(fp, row, col, -num1);
                    Fprint_Cell(fp, row, col, -num2);
                    fprintf(fp, "0\n");
                    num_lines++;
                }
            }
        }
    }

    // 约束3：对于每行，每行包含1-9，子句数：9*9
    for (int row = 0; row < 9; row++) {
        for (int num = 1; num <= 9; num++) {
            for (int col = 0; col < 9; col++) {
                Fprint_Cell(fp, row, col, num);
            }
            fprintf(fp, "0\n");
            num_lines++;
        }
    }

    // 约束4：对于每行，每行不能出现重复，子句数9*9*9

    for (int row = 0; row < 9; row++) {
        for (int num1 = 1; num1 <= 9; num1++) {
            for (int num2 = num1 + 1; num2 <= 9; num2++) {
                for (int col = 0; col < 9; col++) {
                    Fprint_Cell(fp, row, col, -num1);
                    Fprint_Cell(fp, row, col, -num2);
                    fprintf(fp, "0\n");
                    num_lines++;
                }
            }
        }
    }

    // 约束5：对于每列，每列包含1-9，子句数：9*9
    for (int col = 0; col < 9; col++) {
        for (int num = 1; num <= 9; num++) {
            for (int row = 0; row < 9; row++) {
                Fprint_Cell(fp, row, col, num);
            }
            fprintf(fp, "0\n");
            num_lines++;
        }
    }
    // 约束6：对于每列，每列不能出现重复，子句数9*9*9
    for (int col = 0; col < 9; col++) {
        for (int num1 = 1; num1 <= 9; num1++) {
            for (int num2 = num1 + 1; num2 <= 9; num2++) {
                for (int row = 0; row < 9; row++) {
                    Fprint_Cell(fp, row, col, -num1);
                    Fprint_Cell(fp, row, col, -num2);
                    fprintf(fp, "0\n");
                    num_lines++;
                }
            }
        }
    }

    // 约束 7：对于每3x3子块，每块包含1-9，子句数：3*3 *9
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            for (int num = 1; num <= 9; num++) {
                for (int i = 0; i < 3; i++) {
                    for (int j = 0; j < 3; j++) {
                        Fprint_Cell(fp, startRow + i, startCol + j, num);
                    }
                }
                fprintf(fp, "0\n");
                num_lines++;
            }
        }
    }

    // 约束 8：对于每3x3子块，每块不能出现重复，子句数：9*36
    for (int startRow = 0; startRow < 9; startRow += 3) {
        for (int startCol = 0; startCol < 9; startCol += 3) {
            for (int num1 = 1; num1 <= 9; num1++) {
                for (int num2 = num1 + 1; num2 <= 9; num2++) {
                    for (int i = 0; i < 3; i++) {
                        for (int j = 0; j < 3; j++) {
                            Fprint_Cell(fp, startRow + i, startCol + j, -num1);
                            Fprint_Cell(fp, startRow + i, startCol + j, -num2);
                            fprintf(fp, "0\n");
                            num_lines++;
                        }
                    }
                }
            }
        }
    }

    // 约束 9：对角线包含1-9，子句数：9*2
    for (int num = 1; num <= 9; num++) {
        for (int i = 0; i < 9; i++) {
            Fprint_Cell(fp, i, i, num);
        }
        fprintf(fp, "0\n");
        for (int i = 0; i < 9; i++) {
            Fprint_Cell(fp, i, 8 - i, num);
        }
        fprintf(fp, "0\n");
    }

    // 约束 10：对角线不能出现重复，子句数36*2
    for (int num1 = 1; num1 <= 9; num1++) {
        for (int num2 = num1 + 1; num2 <= 9; num2++) {
            for (int i = 0; i < 9; i++) {
                Fprint_Cell(fp, i, i, -num1);
                Fprint_Cell(fp, i, i, -num2);
                fprintf(fp, "0\n");
            }

            for (int i = 0; i < 9; i++) {
                Fprint_Cell(fp, i, 8 - i, -num1);
                Fprint_Cell(fp, i, 8 - i, -num2);
                fprintf(fp, "0\n");
            }
        }
    }
    rewind(fp);
    // 输出变量数、子句数
    fprintf(fp, "p cnf %d %d\n", 729, num_lines);
    fclose(fp);
}

void Print_Board()
{
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) {
                printf("| ");
            }
            printf("%d ", board[i][j]);
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("------+-------+------\n");
        }
    }
}

void Answer_Board()
{
    printf("-----------------------\n");
    printf("Answer:\n");
    printf("-----------------------\n");

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (j == 3 || j == 6) {
                printf("| ");
            }
            board[i][j] = Eval_Cell(i, j);
            printf("%d ", board_ans[i][j]);
        }
        printf("\n");
        if (i == 2 || i == 5) {
            printf("------+-------+------\n");
        }
    }

    printf("\n");
}

void Export_Solution_Res_File(bool is_sat)
{
    FILE *fp = fopen("solution.res", "w");
    if (fp == NULL) {
        printf("Error: cannot create file\n");
        exit(1);
    }

    if (is_sat) {
        fprintf(fp, "s 1\nv");
        for (int i = 1; i <= num_vars; ++i) {
            fprintf(fp, " %d", (model[i] ? i : -i));
        }
    } else {
        fprintf(fp, "s 0\nv");
    }
    fprintf(fp, "\nt %d", elapse_time);

    fclose(fp);
    // 当前路径
    printf("Solution saved to %s/solution.res\n", getcwd(NULL, 0));
}

int Solver(int argc, const char *argv[])
{
    // parse command line options
    if (argc == 1) {
        // gui
    } else {
        // cli
    }

    if (argc > 1) { // 读取SAT问题文件，并初始化其他必要的变量
        const char *filename = argv[1];
        printf("\nReading SAT problem from file %s\n", filename);
        Create_CNF_From_File(filename);
    } else { // Sudoku
        is_sudoku = true;
        Read_Board_From_File("tstsudoku.txt");
        Print_Board();
        printf("\n");
        const char *filename = "tst.cnf";
        Board_To_CNF(board, filename);
        Create_CNF_From_File(filename);
    }

    Init_IntStack(&backtrack_stack); // 初始化回溯栈

    // 记录时间(全局变量)
    start_time = clock();

    // 处理初始单位子句，如果有的话
    Preprocess_Unit_Clause();

    // 执行主DPLL过程
    DPLL();

    return 0;
}