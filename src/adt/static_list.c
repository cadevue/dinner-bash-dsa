#include "static_list.h"
#include <stdio.h>
#include <stdlib.h>

void ResetStaticList(StaticList *list, char type) {
    list->type = type;
    list->count = 0;
    for (int i = 0; i < NUM_OF_ACTIONS; i++) {
        list->actionCount[i] = 0;
    }
}

char GetStaticListCount(const StaticList *list) { return list->count; }
bool IsStaticListFull(const StaticList *list) { return list->count == STATIC_LIST_CAPACITY; }
bool IsStaticListEmpty(const StaticList *list) { return list->count == 0; }

StaticListElement* GetStaticListElement(StaticList *list, int index)
{
    if (index < 0 || index >= list->count) {
        return NULL;
    }

    return &list->data[index];
}


FoodType* FindFoodTypeById(StaticList *list, int id) {
    for (int i = 0; i < list->count; i++) {
        if (list->data[i].foodType.id == id) {
            return &list->data[i].foodType;
        }
    }

    return NULL;
}

int FindFoodTypesByAction(StaticList *list, char action, FoodType **dest) {
    int count = 0;
    for (int i = 0; i < list->count; i++) {
        if (list->data[i].foodType.actionType == action) {
            dest[count] = &list->data[i].foodType;
            count++;
        }
    }

    return count;
}

int GetCountByActionType(StaticList *list, char action) {
    return list->actionCount[action];
}

void InsertLastStaticList(StaticList *list, StaticListElement element) {
    list->data[list->count] = element;
    list->count++;
    if (list->type == TYPE_FOOD) {
        list->actionCount[element.foodType.actionType]++;
    }
}

void FreeStaticList(StaticList *list) {
    for (int i = 0; i < list->count; i++)
    {
        if (list->type == TYPE_RECIPE) {
            free(list->data[i].recipe);
        }
    }

    ResetStaticList(list, list->type);
}