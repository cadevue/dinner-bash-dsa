#pragma once
// Note: This is a simple map implementation that uses a linked list to store key-value pairs.
// Why not use a hash table? For the use case of this project, I think hash table will cause even more overhead.

typedef struct MapNode
{
    int key;
    int value;
    struct MapNode *next;
} MapNode;

typedef struct
{
    MapNode* head;
    int count;
} Map;

void ResetMap(Map *map);
void SetMapValue(Map *map, int key, int value);
int GetMapValue(Map *map, int key);
void FreeMap(Map *map);
