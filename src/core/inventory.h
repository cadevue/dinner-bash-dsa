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
bool IsInventoryEmpty(const Inventory *inventory);
int GetInventoryCount(const Inventory *inventory);
Food* GetInventoryElement(Inventory *inventory, int index);
Food RemoveInventoryElement(Inventory *inventory, int index);
void InsertInventory(Inventory *inventory, Food food);
void UpdateInventory(Inventory *inventory, const Time* currentTime);
void FreeInventory(Inventory *inventory);