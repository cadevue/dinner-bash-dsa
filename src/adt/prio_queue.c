#include "prio_queue.h"
#include <stdlib.h>
#include <stdio.h>

void ResetPrioQueue(PrioQueue *queue) {
    queue->head = nullptr;
    queue->count = 0;
}

void FreePrioQueue(PrioQueue *queue) {
    PrioQueueElement *current = queue->head;
    while (current != nullptr) {
        PrioQueueElement *next = current->next;
        free(current);
        current = next;
    }

    ResetPrioQueue(queue);
}

bool IsPrioQueueEmpty(const PrioQueue *queue) {
    return queue->count == 0;
}

void EnqueuePrioQueue(PrioQueue *queue, PrioQueueElementData data, char priority) {
    PrioQueueElement *element = (PrioQueueElement *) malloc(sizeof(PrioQueueElement));
    element->data = data;
    element->priority = priority;
    element->next = nullptr;

    if (queue->head == nullptr) {
        queue->head = element;
    } else {
        PrioQueueElement *current = queue->head;
        PrioQueueElement *prev = nullptr;
        while (current != nullptr && current->priority <= priority) {
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            element->next = queue->head;
            queue->head = element;
        } else {
            prev->next = element;
            element->next = current;
        }
    }

    queue->count++;
}

PrioQueueElementData DequeuePrioQueue(PrioQueue *queue) {
    if (queue->head == nullptr) {
        return (PrioQueueElementData) {0};
    }

    PrioQueueElement *element = queue->head;
    PrioQueueElementData data = element->data;

    queue->head = element->next;
    free(element);

    queue->count--;

    return data;
}

void PrintPrioQueue(const PrioQueue *queue) {
    PrioQueueElement *current = queue->head;
    while (current != nullptr) {
        printf("Priority: %d\n", current->priority);
        current = current->next;
    }
}