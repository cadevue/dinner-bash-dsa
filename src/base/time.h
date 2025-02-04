#pragma once
#include "boolean.h"

typedef struct {
    char day;
    char hour;   // [0..23]
    char minute; // [0..59]
} Time;

#define Duration Time

char GetDay(const Time *t);
char GetHour(const Time *t);
char GetMinute(const Time *t);

void AddDay(Time *t, char day);
void AddHour(Time *t, char hour);
void AddMinute(Time *t, char minute);

void AddDuration(Time *t, Duration *duration);

bool IsEqOrLater(const Time *t1, const Time *t2);

void PrintTime(const Time *t);