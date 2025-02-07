#pragma once
#include "food.h"
#include "time.h"
#include "inventory.h"

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
bool IsDeliveryQueueEmpty(const DeliveryQueue *deliveryQueue);
int GetDeliveryQueueCount(const DeliveryQueue *deliveryQueue);
void InsertDeliveryQueue(DeliveryQueue *deliveryQueue, const FoodType *foodType, const Time *currentTime);
void UpdateDeliveryQueue(DeliveryQueue *deliveryQueue, Inventory *inventory, const Time *currentTime);
void FreeDeliveryQueue(DeliveryQueue *deliveryQueue);