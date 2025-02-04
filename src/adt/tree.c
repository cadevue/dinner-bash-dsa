#include "tree.h"

void ResetTree(Tree *tree) {
    tree->childCount = 0;
}

void FreeTree(Tree *tree) {
    for (int i = 0; i < tree->childCount; i++) {
        FreeTree(tree->children[i]);
    }
}

bool IsTreeEmpty(const Tree *tree) {
    return tree->childCount == 0;
}

bool IsTreeChildrenFull(const Tree *tree) {
    return tree->childCount == MAX_TREE_CHILD_COUNT;
}

bool IsTreeLeaf(const Tree *tree) {
    return tree->childCount == 0;
}

void AddChild(Tree *tree, Tree *child) {
    if (IsTreeChildrenFull(tree)) {
        return;
    }

    tree->children[tree->childCount] = child;
    tree->childCount++;
}

void RemoveChild(Tree *tree, int index) {
    if (index < 0 || index >= tree->childCount) {
        return;
    }

    FreeTree(tree->children[index]);
    for (int i = index; i < tree->childCount - 1; i++) {
        tree->children[i] = tree->children[i + 1];
    }
    tree->childCount--;
}

Tree *GetChild(const Tree *tree, int index) {
    if (index < 0 || index >= tree->childCount) {
        return nullptr;
    }

    return tree->children[index];
}

TreeData GetData(const Tree *tree) {
    return tree->data;
}

int GetChildCount(const Tree *tree) {
    return tree->childCount;
}