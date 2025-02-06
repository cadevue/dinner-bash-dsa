#include "tree.h"

void ResetTree(Tree *tree) {
    tree->childCount = 0;
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

Tree *GetChild(const Tree *tree, int index) {
    if (index < 0 || index >= tree->childCount) {
        return nullptr;
    }

    return tree->children[index];
}

int GetData(const Tree *tree) {
    return tree->data;
}

int GetChildCount(const Tree *tree) {
    return tree->childCount;
}