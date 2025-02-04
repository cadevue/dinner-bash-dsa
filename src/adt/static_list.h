#include "boolean.h"
#include <stdlib.h>

#define STATIC_LIST_CAPACITY 50
#define SL_ELMT_EQUAL(e1, e2) (e1.i == e2.i || e1.f == e2.f)

#define TYPE_INT 0
#define TYPE_FLOAT 1

typedef union {
    int i;
    float f;
    /* data */
} StaticListElement;


/**  Static List is a fixed-size list with maximum size of ARRAY_SIZE */
typedef struct {
    StaticListElement data[STATIC_LIST_CAPACITY];
    int type;
    int count;
} StaticList;

void ResetStaticList(StaticList *list);
int GetStaticListCount(const StaticList *list);

bool IsStaticListFull(const StaticList *list);
bool IsStaticListEmpty(const StaticList *list);

int GetIndexOfStaticList(const StaticList *list, StaticListElement element);

void InsertFirstStaticList(StaticList *list, StaticListElement element);
void InsertLastStaticList(StaticList *list, StaticListElement element);
void InsertAtStaticList(StaticList *list, int index, StaticListElement element);

StaticListElement RemoveFirstStaticList(StaticList *list);
StaticListElement RemoveLastStaticList(StaticList *list);
StaticListElement RemoveAtStaticList(StaticList *list, int index);

void PrintStaticList(const StaticList *list);