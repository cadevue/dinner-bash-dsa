#pragma once

#include "boolean.h"

typedef struct {
    int day;
    int hour;   // [0..23]
    int minute; // [0..59]
} Time;

#define Duration Time

void ResetTime(Time *t, int day, int hour, int minute);

int GetDay(const Time *t);
int GetHour(const Time *t);
int GetMinute(const Time *t);

void AddDay(Time *t, int day);
void AddHour(Time *t, int hour);
void AddMinute(Time *t, int minute);

void AddDuration(Time *t, const Duration *duration);

bool IsEqOrLater(const Time *t1, const Time *t2);
Duration DurationBetween(const Time *t1, const Time *t2);

void PrintTime(const Time *t);
void DurationToString(const Duration *duration, char *buffer);