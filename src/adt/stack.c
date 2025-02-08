#include "stack.h"
#include "../core/action.h"

void ResetStack(Stack *stack) {
    stack->top = -1;
}

bool IsStackEmpty(Stack *stack) {
    return stack->top == -1;
}

bool IsStackFull(Stack *stack) {
    return stack->top == MAX_STACK_SIZE - 1;
}

void StackPush(Stack *stack, StackElement value) {
    if (IsStackFull(stack)) {
        // shift all elements to the left
        for (int i = 0; i < MAX_STACK_SIZE - 1; i++) {
            stack->data[i] = stack->data[i + 1];
        }
    } else {
        stack->top++;
    }
        stack->data[stack->top] = value;
}

StackElement StackPop(Stack *stack) {
    if (!IsStackEmpty(stack)) {
        return stack->data[stack->top--];
    }
    return (StackElement) {ACTION_INVALID, 0, 0};
}

StackElement StackPeek(Stack *stack) {
    return stack->data[stack->top];
}

void ClearStack(Stack *stack) {
    ResetStack(stack);
}
