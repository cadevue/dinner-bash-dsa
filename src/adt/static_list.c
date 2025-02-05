#include "static_list.h"
#include <stdio.h>

void ResetStaticList(StaticList *list) {
    list->count = 0;
}

char GetStaticListCount(const StaticList *list) {
    return list->count;
}

bool IsStaticListFull(const StaticList *list) { 
    return list->count == STATIC_LIST_CAPACITY;
}

bool IsStaticListEmpty(const StaticList *list) { 
    return list->count == 0;
}

char GetIndexOfStaticList(const StaticList *list, StaticListElement element) {
    for (int i = 0; i < list->count; i++) {
        if (SL_ELMT_EQUAL(list->data[i], element)) {
            return i;
        }
    }

    return -1;
}

void InsertFirstStaticList(StaticList *list, StaticListElement element) {
    list->count++;

    // Shift all elements to the right
    for (int i = list->count - 1; i > 0; i--) {
        list->data[i] = list->data[i - 1];
    }

    // Insert the element at the first index
    list->data[0] = element;
}

void InsertLastStaticList(StaticList *list, StaticListElement element) {
    list->data[list->count] = element;
    list->count++;
}

void InsertAtStaticList(StaticList *list, int index, StaticListElement element) {
    if (index < 0 || index > list->count) {
        return;
    }

    if (index == list->count) {
        InsertLastStaticList(list, element);
        return;
    } else if (index == 0) {
        InsertFirstStaticList(list, element);
        return;
    } else {
        list->count++;

        // Shift data after the index to the right
        for (int i = list->count - 1; i > index; i--) {
            list->data[i] = list->data[i - 1];
        }
        list->data[index] = element;
    }
}

StaticListElement RemoveFirstStaticList(StaticList *list) {
    if (list->count == 0) {
        return (StaticListElement) {0};
    }

    StaticListElement element = list->data[0];
    list->count--;

    // Shift all elements to the left
    for (int i = 0; i < list->count; i++) {
        list->data[i] = list->data[i + 1];
    }

    return element;
}

StaticListElement RemoveLastStaticList(StaticList *list) {
    if (list->count == 0) {
        return (StaticListElement) {0};
    }

    list->count--;
    return list->data[list->count];

}
StaticListElement RemoveAtStaticList(StaticList *list, int index) {
    if (index < 0 || index >= list->count) {
        return (StaticListElement) {0};
    }

    StaticListElement element = list->data[index];
    list->count--;

    // Shift all elements after the index to the left
    for (int i = index; i < list->count; i++) {
        list->data[i] = list->data[i + 1];
    }

    return element;

}

void PrintStaticList(const StaticList *list) {
    printf("[");
    for (int i = 0; i < list->count; i++) {
        if (list->type == TYPE_FOOD) {
            printf("%s,", list->data[i].foodType.name);
        } else if (list->type == TYPE_RECIPE) {
            printf("%d,", list->data[i].recipe.data.foodId);
        } else {
            printf("Unknown type\n");
            break;
        }
    }

    printf("]\n");
}