#include "delivery.h"
#include "log.h"

#include <stdlib.h>
#include <stdio.h>

void ResetDeliveryQueue(DeliveryQueue *deliveryQueue) {
    deliveryQueue->head = nullptr;
    deliveryQueue->count = 0;
}

int GetIndexOfDeliveryQueue(const DeliveryQueue *deliveryQueue, Food food) {
    DeliveryQueueEntry *current = deliveryQueue->head;
    int index = 0;
    while (current != nullptr) {
        if (current->foodType->id == food.type->id) {
            return index;
        }

        current = current->next;
        index++;
    }

    return -1;
}

DeliveryQueueEntry* GetDeliveryQueueElement(DeliveryQueue *deliveryQueue, int index) {
    DeliveryQueueEntry *current = deliveryQueue->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return current;
}

void InsertDeliveryQueue(DeliveryQueue *deliveryQueue, const FoodType *foodType, const Time* currentTime) {
    DeliveryQueueEntry *entry = (DeliveryQueueEntry *) malloc(sizeof(DeliveryQueueEntry));
    entry->foodType = foodType;
    entry->deliveredTime = *currentTime;
    AddDuration(&entry->deliveredTime, &foodType->timeToDeliver);
    AddMinute(&entry->deliveredTime, 1); // Add 1 minute to make sure the item is delivered in the next minute

    entry->next = nullptr;

    if (deliveryQueue->head == nullptr) {
        deliveryQueue->head = entry;
    } else {
        DeliveryQueueEntry *current = deliveryQueue->head;
        DeliveryQueueEntry *prev = nullptr;
        while (current != nullptr && IsEqOrLater(currentTime, &current->deliveredTime)) {
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            entry->next = deliveryQueue->head;
            deliveryQueue->head = entry;
        } else {
            prev->next = entry;
            entry->next = current;
        }
    }

    char message[128];
    char duration[32];
    DurationToString(&foodType->timeToDeliver, duration);
    sprintf(message, "%s order successful! Item will be delivered in %s", foodType->name, duration);
    AddLogMessage(message);
    deliveryQueue->count++;
}

void UpdateDeliveryQueue(DeliveryQueue *deliveryQueue, Inventory* inventory, const Time *currentTime) {
    DeliveryQueueEntry *current = deliveryQueue->head;
    char message[128];
    while (current != nullptr && IsEqOrLater(currentTime, &current->deliveredTime)) {
        Food food;
        ResetFood(&food, current->foodType, current->deliveredTime);
        InsertInventory(inventory, food);

        sprintf(message, "Item %s is delivered! the item has been added to inventory!", current->foodType->name);
        AddLogMessage(message);

        deliveryQueue->head = current->next;
        free(current);
        deliveryQueue->count--;

        current = deliveryQueue->head;
    }
}

void FreeDeliveryQueue(DeliveryQueue *deliveryQueue) {
    DeliveryQueueEntry *current = deliveryQueue->head;
    while (current != nullptr) {
        DeliveryQueueEntry *next = current->next;
        free(current);
        current = next;
    }

    ResetDeliveryQueue(deliveryQueue);
}
