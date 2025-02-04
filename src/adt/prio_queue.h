#pragma once
#include "../base/food.h"

#define PRIO_Q_ALLOC_CONST 1.5f

typedef union {
    Food food;
} PrioQueueElementData;

typedef struct {
    PrioQueueElementData data;
    char priority;
} PrioQueueElement;

typedef struct {
    PrioQueueElement *data;
    int count;
    int capacity;
} PrioQueue;

void ResetPrioQueue(PrioQueue *queue, int capacity);
void FreePrioQueue(PrioQueue *queue);

bool IsPrioQueueFull(const PrioQueue *queue);
bool IsPrioQueueEmpty(const PrioQueue *queue);

void EnqueuePrioQueue(PrioQueue *queue, PrioQueueElementData data, char priority);
PrioQueueElementData DequeuePrioQueue(PrioQueue *queue);

void PrintPrioQueue(const PrioQueue *queue);

void ExpandPrioQueue(PrioQueue *queue, int addedCapacity);
void ShrinkPrioQueue(PrioQueue *queue, int reducedCapacity);
void CompactPrioQueue(PrioQueue *queue);
