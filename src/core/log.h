#pragma once

#define MAX_LOG_COUNT 8
#define MAX_MESSAGE_LENGTH 200

typedef struct {
    char logQueue[MAX_MESSAGE_LENGTH][MAX_LOG_COUNT];
    int count;
} Log;

void ResetLog(Log* log);
void AddLogMessage(Log* log, const char* message);
void GetLogQueue(Log* log, char dest[MAX_LOG_COUNT][MAX_MESSAGE_LENGTH]);
int GetLogCount(const Log* log);