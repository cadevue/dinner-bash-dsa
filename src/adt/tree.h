#pragma once

#include "../core/boolean.h"

#define MAX_TREE_CHILD_COUNT 5

typedef struct Tree
{
    int data;
    int childCount;
    struct Tree *children[MAX_TREE_CHILD_COUNT];
} Tree;

void ResetTree(Tree *tree);

bool IsTreeEmpty(const Tree *tree);
bool IsTreeChildrenFull(const Tree *tree);
bool IsTreeLeaf(const Tree *tree);

void AddChild(Tree *tree, Tree *child);

Tree *GetChild(const Tree *tree, int index);
int GetData(const Tree *tree);
int GetChildCount(const Tree *tree);