#pragma once
#include "../base/food.h"

#define PRIO_Q_ALLOC_CONST 1.5f

typedef union {
    Food food;
} PrioQueueElementData;

typedef struct {
    PrioQueueElementData data;
    char priority;
    PrioQueueElement *next;
} PrioQueueElement;

typedef struct {
    PrioQueueElement *head;
    int count;
} PrioQueue;

void ResetPrioQueue(PrioQueue *queue);
void FreePrioQueue(PrioQueue *queue);

bool IsPrioQueueEmpty(const PrioQueue *queue);

void EnqueuePrioQueue(PrioQueue *queue, PrioQueueElementData data, char priority);
PrioQueueElementData DequeuePrioQueue(PrioQueue *queue);

void PrintPrioQueue(const PrioQueue *queue);