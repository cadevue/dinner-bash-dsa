#pragma once
#include "../base/boolean.h"

#define STACK_MAX_CAPACITY 75

typedef union {
    char c;
} StackElement;

typedef struct {
    StackElement data[STACK_MAX_CAPACITY];
    int count;
} Stack;

void ResetStack(Stack *stack);
char GetStackCount(const Stack *stack);

bool IsStackFull(const Stack *stack);
bool IsStackEmpty(const Stack *stack);

void PushStack(Stack *stack, StackElement element);
StackElement PopStack(Stack *stack);
StackElement PeekStack(const Stack *stack);