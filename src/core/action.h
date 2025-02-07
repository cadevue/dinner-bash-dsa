#pragma once

#define ACTION_INVALID  0

// Also is a valid tile value
#define ACTION_NONE     1
#define ACTION_BUY      2
#define ACTION_MIX      3
#define ACTION_CHOP     4
#define ACTION_FRY      5
#define ACTION_BOIL     6
#define ACTION_OBSTACLE 7

// Pure actions
#define ACTION_MOVE_U   8
#define ACTION_MOVE_R   9
#define ACTION_MOVE_D   10
#define ACTION_MOVE_L   11
#define ACTION_WAIT     12

#define ACTION_USE_FOR_RECIPE 13

// Revert actions
#define ACTION_UNDO_WAIT     16
#define ACTION_REVERT_RECIPE 17
#define ACTION_REVERT_BUY    18

#define ACTION_SIM_POS  99

char GetSymbolForAction(char action);
void GetActionName(char action, char *buffer);
char NameToAction(const char *buffer);
char GetOppositeAction(char action);