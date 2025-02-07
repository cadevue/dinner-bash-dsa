#pragma once
#include "food.h"
#include "time.h"

typedef struct InventoryElement {
    Food data;
    struct InventoryElement *next;
} InventoryElement;

typedef struct {
    InventoryElement *head;
    int count;
} Inventory;

void ResetInventory(Inventory *inventory);
int GetInventoryAmountOfType(const Inventory *inventory, const FoodType *type);
Food* GetInventoryElement(Inventory *inventory, int index);
Food* GetInventoryElementOfType(Inventory *inventory, const FoodType *type);
Food RemoveInventoryElement(Inventory *inventory, int index);
Food RemoveInventoryElementOfType(Inventory *inventory, const FoodType *type);
void InsertInventory(Inventory *inventory, Food food);
void UpdateInventory(Inventory *inventory, const Time* currentTime);
void FreeInventory(Inventory *inventory);