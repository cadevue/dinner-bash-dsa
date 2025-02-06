#include "time.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

void ResetTime(Time *t, int day, int hour, int minute) {
    t->day = day;
    t->hour = hour;
    t->minute = minute;
}

int GetDay(const Time *t) { return t->day; }
int GetHour(const Time *t) { return t->hour; }
int GetMinute(const Time *t) { return t->minute; }

void AddDay(Time *t, int day) { 
    t->day += day;
}

void AddHour(Time *t, int hour) {
    t->hour += hour;
    if (t->hour > 23) {
        AddDay(t, t->hour / 24);
        t->hour = t->hour % 24;
    }
}

void AddMinute(Time *t, int minute) {
    t->minute += minute;
    if (t->minute > 59) {
        AddHour(t, t->minute / 60);
        t->minute = t->minute % 60;
    } else if (t->minute < 0) {
        AddHour(t, t->minute / 60 - 1);
        t->minute = 60 + t->minute % 60;
    }
}

void AddDuration(Time *t, Duration *duration) {
    AddDay(t, duration->day);
    AddHour(t, duration->hour);
    AddMinute(t, duration->minute);
}

bool IsEqOrLater(const Time *t1, const Time *t2) {
    if (t1->day > t2->day) {
        return true;
    } else if (t1->day == t2->day) {
        if (t1->hour > t2->hour) {
            return true;
        } else if (t1->hour == t2->hour) {
            if (t1->minute >= t2->minute) {
                return true;
            }
        }
    }

    return false;
}

void PrintTime(const Time *t) {
    printf("Day %d, %02d:%02d\n", t->day, t->hour, t->minute);
}