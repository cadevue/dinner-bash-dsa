#include "stack.h"
#include "../core/action.h"

void ResetStack(Stack *stack) {
    stack->top = -1;
}

bool IsEmpty(Stack *stack) {
    return stack->top == -1;
}

bool IsFull(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void Push(Stack *stack, StackElement value) {
    if (IsFull(stack)) {
        // shift all elements to the left
        for (int i = 0; i < MAX_STACK_SIZE - 1; i++) {
            stack->data[i] = stack->data[i + 1];
        }
    } else {
        stack->top++;
    }
}

StackElement Pop(Stack *stack) {
    if (!IsEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return (StackElement) {ACTION_INVALID, 0, 0};
}

StackElement Peek(Stack *stack) {
    return stack->data[stack->top];
}
