#include "stack.h"
void ResetStack(Stack *stack) {
    stack->count = 0;
}

char GetStackCount(const Stack *stack) {
    return stack->count;
}

bool IsStackFull(const Stack *stack) {
    return stack->count == STACK_MAX_CAPACITY;
}

bool IsStackEmpty(const Stack *stack) {
    return stack->count == 0;
}

void PushStack(Stack *stack, StackElement element) {
    if (IsStackFull(stack)) {
        return;
    }

    stack->data[stack->count] = element;
    stack->count++;
}

StackElement PopStack(Stack *stack) {
    if (IsStackEmpty(stack)) {
        return (StackElement) {0};
    }

    stack->count--;
    return stack->data[stack->count];
}

StackElement PeekStack(const Stack *stack) {
    if (IsStackEmpty(stack)) {
        return (StackElement) {0};
    }

    return stack->data[stack->count - 1];
}