#pragma once

#include "myIntStack.h"
#include "myIntVector.h"
#include "Sudoku.h"

#define Weight_Increment 1.0
#define Weight_Update 1000
#define DECISION_MARK 0
#define TIME_LIMIT 3 // 8 seconds

#define TRUE 1
#define FALSE 0
#define UNDEFINED -1
// 0: heuristic conflicts counter. 
// 1: most appearances. 
// 2. nearest
int SPLIT_STRATEGY = 2; 


// 全局变量
int *model;                          // 记录变量取值
int *clause_mask;                    // 记录子句是否可跳过
int *num_undef_each_clause;          // 记录每个子句中未确定变量的数量
IntStack backtrack_stack;            // 回溯栈
IntVector *clauses;                  // clauses[num_clauses],子句集
IntVector *clauses_contain_positive; // clauses_contain_positive[num_vars+1]每个正字面所在的子句的集
IntVector *clauses_contain_negative; // clauses_contain_negative[num_vars+1]每个负字面所在的子句的集

int num_vars, num_clauses;        // 变元数、子句数
int decision_level;               // 决策等级
int conflicts;                    // 次数统计
int idx_next_literal;             // 指向下一个从回溯栈中传播的字面
double *positive_literal_weights; // 正字面权重
double *negative_literal_weights; // 负字面权重
clock_t start_time, end_time;     // 计时器
int elapse_time;                  // 运行时间

bool is_sudoku = false; // 是否为数独
bool is_sudoku_gui = true; 
bool IS_SAT = false; 
bool enableTLE = true; 
int board_given = 28;
int board[9][9] = {0}; // 数独
int board_ans[9][9] = {0}; // 数独
int board_mask[9][9] = {0}; // 用于记录已填入数字的位置


int Abs(int literal);

// SAT functions declaration
void Create_CNF_From_File(const char *filename);

int Eval_Literal(int literal);
void Correct_Literal(int literal);

void Preprocess_Unit_Clause();
void Update_Mask(int literal, bool is_push);
void Update_Weights(IntVector clause);
int Get_Next_Decision_Literal();

bool IsPropagateToConflict();
void Learn_From_Conflict(IntVector conflict_clause);
void DPLL();

void Exit_With_Stat(bool is_sat);
void Export_Solution_Res_File(bool is_sat);
void Verify();


// Xsudoku functions declaration
int IJK_To_Literal(int row, int col, int num);
int Literal_To_IJK(int literal, int *row, int *col, int *num);

int Eval_Cell(int row, int col);
void Fprint_Cell(FILE *fp, int row, int col, int num);

void Read_Board_From_String(char *str);
void Read_Board_From_File(const char *filename);
void Print_Board();
void Answer_Board();

void Board_To_CNF(int board[9][9], const char *out_filename);

void Generate_XSudoku_And_Answer(int board[9][9], int given, int board_answer[9][9]);



