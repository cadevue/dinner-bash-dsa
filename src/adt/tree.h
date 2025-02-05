#pragma once
#include "../base/boolean.h"

#define MAX_TREE_CHILD_COUNT 5

typedef union {
    int foodId;
} TreeData;

typedef struct Tree
{
    TreeData data;
    int childCount;
    struct Tree *children[MAX_TREE_CHILD_COUNT];
} Tree;

void ResetTree(Tree *tree);
void FreeTree(Tree *tree);

bool IsTreeEmpty(const Tree *tree);
bool IsTreeChildrenFull(const Tree *tree);
bool IsTreeLeaf(const Tree *tree);

void AddChild(Tree *tree, Tree *child);
void RemoveChild(Tree *tree, int index);

Tree *GetChild(const Tree *tree, int index);
TreeData GetData(const Tree *tree);
int GetChildCount(const Tree *tree);
