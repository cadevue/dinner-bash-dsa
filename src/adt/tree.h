#pragma once

#include "../core/boolean.h"
#include "../core/food.h"

#define MAX_TREE_CHILD_COUNT 5

typedef struct Tree
{
    FoodType *data;
    int childCount;
    struct Tree *children[MAX_TREE_CHILD_COUNT];
} Tree;

void ResetTree(Tree *tree, FoodType *data);
void AddChild(Tree *tree, Tree *child);
Tree* GetChild(const Tree *tree, int index);
int GetChildCount(const Tree *tree);