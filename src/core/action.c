#include "action.h"
#include <string.h>

char GetSymbolForAction(char action) {
    switch (action) {
        case ACTION_NONE: return ' ';
        case ACTION_OBSTACLE: return 'X';
        case ACTION_BUY: return 'T';
        case ACTION_MIX: return 'M';
        case ACTION_CHOP: return 'C';
        case ACTION_FRY: return 'F';
        case ACTION_BOIL: return 'B';
        default: return '*';
    }
}

void GetActionName(char action, char *buffer) {
    switch (action) {
        case ACTION_BUY: strcpy(buffer, "Buy"); break;
        case ACTION_MIX: strcpy(buffer, "Mix"); break;
        case ACTION_CHOP: strcpy(buffer, "Chop"); break;
        case ACTION_FRY: strcpy(buffer, "Fry"); break;
        case ACTION_BOIL: strcpy(buffer, "Boil"); break;
        default: strcpy(buffer, "Unknown");
    }
}

char NameToAction(const char *buffer) {
    if (strcasecmp(buffer, "Buy") == 0) return ACTION_BUY;
    if (strcasecmp(buffer, "Mix") == 0) return ACTION_MIX;
    if (strcasecmp(buffer, "Chop") == 0) return ACTION_CHOP;
    if (strcasecmp(buffer, "Fry") == 0) return ACTION_FRY;
    if (strcasecmp(buffer, "Boil") == 0) return ACTION_BOIL;
    return ACTION_INVALID;
}