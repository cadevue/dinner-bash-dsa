#include "time.h"
#include "boolean.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void AddDuration(Time *t, const Duration *duration) {
    AddDay(t, duration->day);
    AddHour(t, duration->hour);
    AddMinute(t, duration->minute);
}

Duration DurationBetween(const Time *t1, const Time *t2) {
    Duration duration;
    duration.day    = t2->day - t1->day;
    duration.hour   = t2->hour - t1->hour;
    duration.minute = t2->minute - t1->minute;

    if (duration.minute < 0) {
        duration.minute += 60;
        duration.hour--;
    }

    if (duration.hour < 0) {
        duration.hour += 24;
        duration.day--;
    }

    return duration;
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

void DurationToString(const Duration *duration, char *dest) {
    memset(dest, 0, sizeof(dest));
    if (duration->day > 0) {
        sprintf(dest, "%d day%s", duration->day, (duration->day > 1) ? "s" : "");
    }

    if (duration->hour > 0) {
        if (strlen(dest) > 0) {
            strcat(dest, ", ");
        }
        char hourStr[32];
        sprintf(hourStr, "%d hour%s", duration->hour, (duration->hour > 1) ? "s" : "");
        strcat(dest, hourStr);
    }

    if (duration->minute > 0) {
        if (strlen(dest) > 0) {
            strcat(dest, ", ");
        }
        char minuteStr[32];
        sprintf(minuteStr, "%d minute%s", duration->minute, (duration->minute > 1) ? "s" : "");
        strcat(dest, minuteStr);
    }

    // If all fields are zero, set the output to "Immediate"
    if (strlen(dest) == 0) {
        strcpy(dest, "Immediate");
    }
}