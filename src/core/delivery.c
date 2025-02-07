#include "delivery.h"
#include <stdlib.h>

void ResetDeliveryQueue(DeliveryQueue *deliveryQueue) {
    deliveryQueue->head = nullptr;
    deliveryQueue->count = 0;
}

bool IsDeliveryQueueEmpty(const DeliveryQueue *deliveryQueue) {
    return deliveryQueue->count == 0;
}

int GetDeliveryQueueCount(const DeliveryQueue *deliveryQueue) {
    return deliveryQueue->count;
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

    deliveryQueue->count++;
}

void UpdateDeliveryQueue(DeliveryQueue *deliveryQueue, const Time *currentTime) {
    DeliveryQueueEntry *current = deliveryQueue->head;
    while (current != nullptr && IsEqOrLater(currentTime, &current->deliveredTime)) {
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
