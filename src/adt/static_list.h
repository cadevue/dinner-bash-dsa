#pragma once
#include "../base/boolean.h"

#define STATIC_LIST_CAPACITY 50
#define SL_ELMT_EQUAL(e1, e2) (e1.c == e2.c)

#define TYPE_INT 0
#define TYPE_FLOAT 1

typedef union {
    char c;
    /* data */
} StaticListElement;


/**  Static List is a fixed-size list with maximum size of STATIC_LIST_CAPACITY */
typedef struct {
    StaticListElement data[STATIC_LIST_CAPACITY];
    char type;
    char count;
} StaticList;

void ResetStaticList(StaticList *list);
char GetStaticListCount(const StaticList *list);

bool IsStaticListFull(const StaticList *list);
bool IsStaticListEmpty(const StaticList *list);

char GetIndexOfStaticList(const StaticList *list, StaticListElement element);

void InsertFirstStaticList(StaticList *list, StaticListElement element);
void InsertLastStaticList(StaticList *list, StaticListElement element);
void InsertAtStaticList(StaticList *list, char index, StaticListElement element);

StaticListElement RemoveFirstStaticList(StaticList *list);
StaticListElement RemoveLastStaticList(StaticList *list);
StaticListElement RemoveAtStaticList(StaticList *list, char index);

void PrintStaticList(const StaticList *list);