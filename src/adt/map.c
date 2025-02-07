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
