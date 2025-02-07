#pragma once
#include "../core/boolean.h"

#define MAX_STACK_SIZE  20
typedef struct {
    int action;
    int param1;
    int param2;
} StackElement;

typedef struct {
    int top;
    StackElement data[MAX_STACK_SIZE];
} Stack;

void ResetStack(Stack *stack);
bool IsEmpty(Stack *stack);
bool IsFull(Stack *stack);
void Push(Stack *stack, StackElement value);
StackElement Pop(Stack *stack);
StackElement Peek(Stack *stack);
