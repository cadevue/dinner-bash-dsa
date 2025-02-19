#pragma once
#include "food.h"
#include "time.h"
#include "inventory.h"
#include "../adt/stack.h"

typedef struct DeliveryQueueEntry {
    const FoodType* foodType;
    Time deliveredTime;
    struct DeliveryQueueEntry *next;
} DeliveryQueueEntry;

typedef struct {
    DeliveryQueueEntry *head;
    int count;
} DeliveryQueue;

void ResetDeliveryQueue(DeliveryQueue *deliveryQueue);
void InsertDeliveryQueue(DeliveryQueue *deliveryQueue, const FoodType *foodType, const Time *currentTime);
void InsertDeliveryQueueWithDeliveredTime(DeliveryQueue *deliveryQueue, const FoodType *foodType, Time deliveredTime);
void RemoveLatestDeliveryQueue(DeliveryQueue *deliveryQueue, const FoodType *foodType);
void UpdateDeliveryQueue(DeliveryQueue *deliveryQueue, Inventory *inventory, const Time *currentTime, Stack *undoStack);
void FreeDeliveryQueue(DeliveryQueue *deliveryQueue);