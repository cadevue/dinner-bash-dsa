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
} Map; // Not a hash map

void ResetMap(Map *map);
void SetMapValue(Map *map, int key, int value);
int GetMapValue(Map *map, int key);
void FreeMap(Map *map);
