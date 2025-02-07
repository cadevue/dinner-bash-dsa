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
bool IsStackEmpty(Stack *stack);
bool IsStackFull(Stack *stack);
void StackPush(Stack *stack, StackElement value);
StackElement StackPop(Stack *stack);
StackElement StackPeek(Stack *stack);
void ClearStack(Stack *stack);
