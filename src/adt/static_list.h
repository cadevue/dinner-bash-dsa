#pragma once

#include "../core/boolean.h"
#include "../core/food.h"
#include "../core/action.h"
#include "tree.h"

#define STATIC_LIST_CAPACITY 50
#define SL_ELMT_EQUAL(e1, e2) (e1.foodType.id == e2.foodType.id || e1.recipe->data == e2.recipe->data)

#define TYPE_FOOD 0
#define TYPE_RECIPE 1

typedef union {
    FoodType foodType;
    Tree* recipe; // The root of the tree
} StaticListElement;


/**  Static List is a fixed-size list with maximum size of STATIC_LIST_CAPACITY */
typedef struct {
    StaticListElement data[STATIC_LIST_CAPACITY];
    int actionCount[NUM_OF_ACTIONS];
    char type;
    int count;
} StaticList;

void ResetStaticList(StaticList *list, char type);
char GetStaticListCount(const StaticList *list);

bool IsStaticListFull(const StaticList *list);
bool IsStaticListEmpty(const StaticList *list);

int GetIndexOfStaticList(const StaticList *list, StaticListElement element);
StaticListElement* GetStaticListElement(StaticList *list, int index);

FoodType* FindFoodTypeById(StaticList *list, int id);
FoodType* FindFoodTypeByAction(StaticList *list, char action, int index);
int GetCountByActionType(StaticList *list, char action);

void InsertFirstStaticList(StaticList *list, StaticListElement element);
void InsertLastStaticList(StaticList *list, StaticListElement element);
void InsertAtStaticList(StaticList *list, int index, StaticListElement element);

StaticListElement RemoveFirstStaticList(StaticList *list);
StaticListElement RemoveLastStaticList(StaticList *list);
StaticListElement RemoveAtStaticList(StaticList *list, int index);

void PrintStaticList(const StaticList *list);
void FreeStaticList(StaticList *list);