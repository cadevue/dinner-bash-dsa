#include "prio_queue.h"

void ResetPrioQueue(PrioQueue *queue, int capacity) {
    queue->data = (PrioQueueElement *) malloc(capacity * sizeof(PrioQueueElement));
    queue->count = 0;
    queue->capacity = capacity;
}

void FreePrioQueue(PrioQueue *queue) {
    free(queue->data);
    queue->data = nullptr;
    queue->count = 0;
    queue->capacity = 0;
}

bool IsPrioQueueFull(const PrioQueue *queue) {
    return queue->count == queue->capacity;
}

bool IsPrioQueueEmpty(const PrioQueue *queue) {
    return queue->count == 0;
}

void EnqueuePrioQueue(PrioQueue *queue, PrioQueueElementData data, char priority) {
    if (IsPrioQueueFull(queue)) {
        ExpandPrioQueue(queue, (int) (queue->capacity * PRIO_Q_ALLOC_CONST));
    }

    int i = queue->count;
    while (i > 0 && queue->data[i - 1].priority < priority) {
        queue->data[i] = queue->data[i - 1];
        i--;
    }

    queue->data[i].data = data;
    queue->data[i].priority = priority;
    queue->count++;
}

PrioQueueElementData DequeuePrioQueue(PrioQueue *queue) {
    if (IsPrioQueueEmpty(queue)) {
        return (PrioQueueElementData) {0};
    }

    PrioQueueElementData data = queue->data[0].data;
    queue->count--;

    for (int i = 0; i < queue->count; i++) {
        queue->data[i] = queue->data[i + 1];
    }

    return data;
}

void PrintPrioQueue(const PrioQueue *queue) {
    printf("[");
    for (int i = 0; i < queue->count; i++) {
        printf("(%d, %d), ", queue->data[i].data.food.type->id, queue->data[i].priority);
    }
    printf("]\n");
}

void ExpandPrioQueue(PrioQueue *queue, int addedCapacity) {
    queue->data = (PrioQueueElement *) realloc(queue->data, (queue->capacity + addedCapacity) * sizeof(PrioQueueElement));
    queue->capacity += addedCapacity;
}

void ShrinkPrioQueue(PrioQueue *queue, int reducedCapacity) {
    queue->data = (PrioQueueElement *) realloc(queue->data, (queue->capacity - reducedCapacity) * sizeof(PrioQueueElement));
    queue->capacity -= reducedCapacity;
}

void CompactPrioQueue(PrioQueue *queue) {
    queue->data = (PrioQueueElement *) realloc(queue->data, queue->count * sizeof(PrioQueueElement));
    queue->capacity = queue->count;
}