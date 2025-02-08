#include "map.h"
#include <stdlib.h>

void ResetMap(Map *map) {
    map->head = NULL;
    map->count = 0;
}

int GetMapValue(Map *map, int key) {
    MapNode *current = map->head;
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
    return 0;
}

void SetMapValue(Map *map, int key, int value) {
    MapNode *current = map->head;
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        current = current->next;
    }

    MapNode *newNode = (MapNode *)malloc(sizeof(MapNode));
    newNode->key = key;
    newNode->value = value;
    newNode->next = map->head;
    map->head = newNode;
    map->count++;
}

void FreeMap(Map *map) {
    MapNode *current = map->head;
    while (current != NULL) {
        MapNode *next = current->next;
        free(current);
        current = next;
    }
    map->head = NULL;
    map->count = 0;
}
