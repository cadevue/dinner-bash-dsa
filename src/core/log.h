#pragma once

#define MAX_LOG_MESSAGE_LENGTH 128
#define MAX_LOG_ENTRIES 12

typedef struct
{
    char logQueue[MAX_LOG_ENTRIES][MAX_LOG_MESSAGE_LENGTH];
    int count;
} Log;

extern Log GlobalLog;

void ResetLog();
void AddLogMessage(const char *message);
void PrintOutLog();
