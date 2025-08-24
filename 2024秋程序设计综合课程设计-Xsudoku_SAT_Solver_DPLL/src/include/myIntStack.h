#pragma once
#include <stdio.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 32
#define CAPACITY_INCREMENT 32 // 扩容的容量增量

#define __DEBUG_INTSTACK__ 0 // 调试开关

typedef struct IntStack {
    int *data;    // 栈的数组
    int top;      // 栈顶指针
    int capacity; // 栈的容量
} IntStack;

/**
 * @brief Debug用，打印栈中元素的值
 * @param stack 栈的指针
 * @return void
 */
void debug_IntStack(IntStack *stack)
{
    for (int i = 0; i <= stack->top; i++) {
        printf("%d ", stack->data[i]);
    }
    printf("\n");
}

/**
 * @brief 创建一个IntStack，初始容量为INITIAL_CAPACITY
 * @return IntStack* 新建的栈的指针
 */
IntStack *create_IntStack()
{
    IntStack *stack = (IntStack *)malloc(sizeof(IntStack));
    stack->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;
    return stack;
}

/**
 * @brief 从空指针初始化IntStack，初始容量为INITIAL_CAPACITY
 * @param stack 栈的指针
 * @return void
 */
void Init_IntStack(IntStack *stack)
{
    stack->data = (int *)malloc(INITIAL_CAPACITY * sizeof(int));
    stack->top = -1;
    stack->capacity = INITIAL_CAPACITY;
}

/**
 * @brief 判断IntStack是否为空
 * @param stack 栈的指针
 * @return int 1表示栈为空，0表示栈不为空
 */
int is_empty_IntStack(IntStack *stack)
{
    return stack->top == -1;
}

/**
 * @brief 入栈操作
 * @param stack 栈的指针
 * @param value 压入栈的值
 * @return void
 */
void push_IntStack(IntStack *stack, int value)
{
    if (stack->top == stack->capacity - 1) {
        stack->capacity += CAPACITY_INCREMENT;
        stack->data = (int *)realloc(stack->data, stack->capacity * sizeof(int));
    }
    stack->data[++stack->top] = value;

    // debug
    if (__DEBUG_INTSTACK__) {
        debug_IntStack(stack);
    }
}

/**
 * @brief 出栈操作
 * @param stack 栈的指针
 * @return void
 */
void pop_IntStack(IntStack *stack)
{
    if (is_empty_IntStack(stack)) {
        printf("IntStack is empty\n");
        exit(1);
    }
    stack->data[stack->top--];

    // debug
    if (__DEBUG_INTSTACK__) {
        debug_IntStack(stack);
    }
}

/**
 * @brief 获取栈顶元素的值，但不弹出栈顶元素
 * @param stack 栈的指针
 * @return int 栈顶元素的值
 */
int peek_IntStack(IntStack *stack)
{
    if (is_empty_IntStack(stack)) {
        printf("IntStack is empty\n");
        exit(1);
    }
    return stack->data[stack->top];
}

/**
 * @brief 销毁IntStack
 * @param stack 栈的指针
 * @return void
 */
void free_IntStack(IntStack *stack)
{
    free(stack->data);
    free(stack);
}
