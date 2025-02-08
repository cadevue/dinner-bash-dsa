#include "inventory.h"
#include "time.h"
#include "log.h"
#include "action.h"
#include "../adt/map.h"
#include "../adt/stack.h"
#include <stdlib.h>
#include <stdio.h>

void ResetInventory(Inventory *inventory) {
    inventory->head = nullptr;
    inventory->count = 0;
}

bool DoRecipe(Inventory *inventory, const Tree *recipe, const Time *currentTime, Stack *undoStack) {
    // Check if possible to do the recipe
    Map occurences;
    ResetMap(&occurences);

    char message[128];
    for (int i = 0; i < recipe->childCount; i++) // Potential Overhead
    {
        FoodType *type = recipe->children[i]->data;
        int required = GetMapValue(&occurences, type->id) + 1;
        int available = GetInventoryAmountOfType(inventory, type);

        if (required > available) {
            FreeMap(&occurences);

            sprintf(message, "Failed to cook %s: Not enough %s", recipe->data->name, type->name);
            AddLogMessage(message);

            return false;
        }
    }

    // Possible
    FreeMap(&occurences);

    for (int i = 0; i < recipe->childCount; i++) {
        FoodType *type = recipe->children[i]->data;
        Food removed = RemoveInventoryElementOfType(inventory, type);
        sprintf(message, "Item %s has been used to make %s", type->name, recipe->data->name);
        AddLogMessage(message);

        StackPush(undoStack, (StackElement) {ACTION_USE_FOR_RECIPE, GetTotalMinutes(&removed.expiredTime), 0});
    }

    Food result;
    ResetFood(&result, recipe->data, *currentTime);

    InsertInventory(inventory, result);

    char duration[32];
    DurationToString(&recipe->data->timeToExpire, duration);
    sprintf(message, "Item %s has been successfully made! Will expire in %s", recipe->data->name, duration);
    AddLogMessage(message);

    StackPush(undoStack, (StackElement) {recipe->data->actionType, recipe->data->id, 0});

    return true;
}

bool RevertRecipe(Inventory *inventory, const Tree *recipe, const Time *currentTime, Stack *undoStack, Stack *redoStack) {
    char message[128];
    
    FoodType *resultType = recipe->data;
    Food result = RemoveInventoryElementOfType(inventory, resultType);
    sprintf(message, "The making of %s has been reverted!", resultType->name);
    AddLogMessage(message);

    for (int i = 0; i < recipe->childCount; i++) {
        FoodType *type = recipe->children[i]->data;
        Food food;

        StackElement element = StackPop(undoStack);
        Duration timeToExpire = TimeFromTotalMinutes(element.param1);
        ResetFoodWithExpired(&food, type, timeToExpire);
        InsertInventory(inventory, food);

        sprintf(message, "Item %s has been restored to inventory!", type->name);
        AddLogMessage(message);
    }

    StackPush(redoStack, (StackElement) {resultType->actionType, resultType->id, 0});
}

int GetInventoryAmountOfType(const Inventory *inventory, const FoodType *type) {
    InventoryElement *current = inventory->head;
    int count = 0;
    while (current != nullptr) {
        if (current->data.type->id == type->id) {
            count++;
        }

        current = current->next;
    }

    return count;
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

Food* GetInventoryElementOfType(Inventory *inventory, const FoodType *type) {
    InventoryElement *current = inventory->head;
    while (current != nullptr) {
        if (current->data.type->id == type->id) {
            return &current->data;
        }

        current = current->next;
    }

    return nullptr;
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

Food RemoveInventoryElementOfType(Inventory *inventory, const FoodType *type) {
    InventoryElement *current = inventory->head;
    InventoryElement *prev = nullptr;
    while (current != nullptr) {
        if (current->data.type->id == type->id) {
            if (prev == nullptr) {
                inventory->head = current->next;
            } else {
                prev->next = current->next;
            }

            Food data = current->data;
            InventoryElement *next = current->next;
            free(current);
            current = next;
            inventory->count--;
            return data;
        } else {
            prev = current;
            current = current->next;
        }
    }
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