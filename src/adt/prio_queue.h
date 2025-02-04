#pragma once
#include "../base/food.h"

#define PRIO_Q_ALLOC_CONST 1.5f

typedef union {
    Food food;
} PrioQueueElementData;

typedef struct PrioQueueElement {
    PrioQueueElementData data;
    char priority;
    struct PrioQueueElement *next;
} PrioQueueElement;

typedef struct {
    PrioQueueElement *head;
    int count;
} PrioQueue;

void ResetPrioQueue(PrioQueue *queue);
void FreePrioQueue(PrioQueue *queue);

bool IsPrioQueueEmpty(const PrioQueue *queue);

void RemoveExpiredFood(PrioQueue *queue, Time currentTime);
void EnqueuePrioQueue(PrioQueue *queue, PrioQueueElementData data, char priority);
PrioQueueElementData DequeuePrioQueue(PrioQueue *queue);

void PrintPrioQueue(const PrioQueue *queue);