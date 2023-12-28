#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    double data;
    struct Node* next;
} Node;

typedef struct Stack {
    Node* top;
} Stack;

Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}

void push(Stack* stack, double value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = value;
    newNode->next = stack->top;
    stack->top = newNode;
}

double pop(Stack* stack) {
    if (stack->top == NULL) {
        printf("Error: Stack is empty.\n");
        exit(1);
    }
    double value = stack->top->data;
    Node* temp = stack->top;
    stack->top = stack->top->next;
    free(temp);
    return value;
}

int main() {
    Stack* stack = createStack();
    char input[100];
    while (fgets(input, sizeof(input), stdin) != NULL) {
        if (input[0] == '+' || input[0] == '-' || input[0] == '*' || input[0] == '/') {
            double operand2 = pop(stack);
            double operand1 = pop(stack);
            double result;
            switch (input[0]) {
                case '+':
                    result = operand1 + operand2;
                    break;
                case '-':
                    result = operand1 - operand2;
                    break;
                case '*':
                    result = operand1 * operand2;
                    break;
                case '/':
                    result = operand1 / operand2;
                    break;
                default:
                    printf("Invalid operator: %c\n", input[0]);
                    exit(1);
            }
            push(stack, result);
        } else {
            double operand = atof(input);
            push(stack, operand);
        }
    }

    if (stack->top != NULL) {
        double result = pop(stack);
        printf("Result: %.2f\n", result);
    } else {
        printf("No result.\n");
    }

    return 0;
}

// 升序排序链表
void sortList(struct Node* head) {
    struct Node* current = head;
    struct Node* index = NULL;
    int temp;

    if (head == NULL) {
        return;
    }

    while (current != NULL) {
        index = current->next;
        while (index != NULL) {
            if (current->data > index->data) {
                temp = current->data;
                current->data = index->data;
                index->data = temp;
            }
            index = index->next;
        }
        current = current->next;
    }
}