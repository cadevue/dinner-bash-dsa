#include "time.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>

char GetDay(const Time *t) { return t->day; }
char GetHour(const Time *t) { return t->hour; }
char GetMinute(const Time *t) { return t->minute; }

void AddDay(Time *t, char day) { 
    t->day += day;
}

void AddHour(Time *t, char hour) {
    t->hour += hour;
    if (t->hour > 23) {
        t->hour = hour % 24;
    }

    AddDay(t, hour / 24);
}

void AddMinute(Time *t, char minute) {
    t->minute += minute;
    if (t->minute > 59) {
        t->minute = minute % 60;
    }

    AddHour(t, minute / 60);
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
    printf("Day %d, %d:%d\n", t->day, t->hour, t->minute);
}