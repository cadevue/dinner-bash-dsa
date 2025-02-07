#include "log.h"
#include <stdio.h>
#include <string.h>

Log GlobalLog;

void ResetLog() {
    for (int i = 0; i < MAX_LOG_ENTRIES; i++) {
        GlobalLog.logQueue[i][0] = '\0';
    }
    GlobalLog.count = 0;
}

void AddLogMessage(const char *message) {
    if (GlobalLog.count < MAX_LOG_ENTRIES) {
        strcpy(GlobalLog.logQueue[GlobalLog.count], message);
        GlobalLog.count++;
    }
}

void PrintOutLog() {
    if (GlobalLog.count == 0) return;

    printf("\n\033[1;33mLog:\033[0m\n");
    for (int i = 0; i < GlobalLog.count; i++) {
        printf("%d. %s\n", i + 1, GlobalLog.logQueue[i]);
    }

    GlobalLog.count = 0;
}
