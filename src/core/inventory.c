#include "inventory.h"
#include "time.h"
#include "log.h"
#include <stdlib.h>
#include <stdio.h>

void ResetInventory(Inventory *inventory) {
    inventory->head = nullptr;
    inventory->count = 0;
}

bool IsInventoryEmpty(const Inventory *inventory) {
    return inventory->count == 0;
}

int GetInventoryCount(const Inventory *inventory) {
    return inventory->count;
}

int GetIndexOfInventory(const Inventory *inventory, Food food) {
    InventoryElement *current = inventory->head;
    int index = 0;
    while (current != nullptr) {
        if (current->data.type->id == food.type->id) {
            return index;
        }

        current = current->next;
        index++;
    }

    return -1;
}

Food* GetInventoryElement(Inventory *inventory, int index) {
    InventoryElement *current = inventory->head;
    for (int i = 0; i < index; i++) {
        current = current->next;
    }

    return &current->data;
}

Food RemoveInventoryElement(Inventory *inventory, int index) {
    InventoryElement *current = inventory->head;
    InventoryElement *prev = nullptr;
    for (int i = 0; i < index; i++) {
        prev = current;
        current = current->next;
    }

    if (prev == nullptr) {
        inventory->head = current->next;
    } else {
        prev->next = current->next;
    }

    Food data = current->data;
    free(current);
    inventory->count--;

    return data;
}

void InsertInventory(Inventory *inventory, Food food) { 
    InventoryElement *element = (InventoryElement *) malloc(sizeof(InventoryElement));
    element->data = food;
    element->next = nullptr;

    if (inventory->head == nullptr) {
        inventory->head = element;
    } else {
        InventoryElement *current = inventory->head;
        InventoryElement *prev = nullptr;
        while (current != nullptr && IsEqOrLater(&food.expiredTime, &current->data.expiredTime)) {
            prev = current;
            current = current->next;
        }

        if (prev == nullptr) {
            element->next = inventory->head;
            inventory->head = element;
        } else {
            prev->next = element;
            element->next = current;
        }
    }

    inventory->count++;

}

void UpdateInventory(Inventory *inventory, const Time* currentTime) {
    InventoryElement *current = inventory->head;
    char message[128];
    while (current != nullptr && IsEqOrLater(currentTime, &current->data.expiredTime)) {
        sprintf(message, "Item %s is expired! the item has been removed from inventory!", current->data.type->name);
        AddLogMessage(message);

        inventory->head = current->next;
        free(current);
        inventory->count--;

        current = inventory->head;
    }
}

void FreeInventory(Inventory *inventory) {
    InventoryElement *current = inventory->head;
    while (current != nullptr) {
        InventoryElement *next = current->next;
        free(current);
        current = next;
    }

    ResetInventory(inventory);
}