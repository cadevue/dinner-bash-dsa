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
char GetOppositeAction(char action) {
    switch (action) {
        case ACTION_MOVE_U: return ACTION_MOVE_D;
        case ACTION_MOVE_R: return ACTION_MOVE_L;
        case ACTION_MOVE_D: return ACTION_MOVE_U;
        case ACTION_MOVE_L: return ACTION_MOVE_R;
        case ACTION_WAIT: return ACTION_UNDO_WAIT;
        case ACTION_BUY: return ACTION_REVERT_BUY;
        case ACTION_MIX: return ACTION_REVERT_RECIPE;
        case ACTION_CHOP: return ACTION_REVERT_RECIPE;
        case ACTION_FRY: return ACTION_REVERT_RECIPE;
        case ACTION_BOIL: return ACTION_REVERT_RECIPE;
        default: return ACTION_INVALID;
    }
}