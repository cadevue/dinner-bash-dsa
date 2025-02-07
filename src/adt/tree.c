#include "tree.h"

void ResetTree(Tree *tree, FoodType *data) {
    tree->childCount = 0;
    tree->data = data;
}

bool IsTreeChildrenFull(const Tree *tree) {
    return tree->childCount == MAX_TREE_CHILD_COUNT;
}

void AddChild(Tree *tree, Tree *child) {
    if (IsTreeChildrenFull(tree)) {
        return;
    }

    tree->children[tree->childCount] = child;
    tree->childCount++;
}

Tree *GetChild(const Tree *tree, int index) {
    if (index < 0 || index >= tree->childCount) {
        return nullptr;
    }

    return tree->children[index];
}

int GetChildCount(const Tree *tree) {
    return tree->childCount;
}