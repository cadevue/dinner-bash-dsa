#include "history.h"
#include "../core/log.h"
#include <string.h>
#include <stdio.h>

static char message[128]; // shared free-to-use buffer for logging purposes

void UndoRecipeAction(Application *app, char action, StackElement element) {
    Tree* recipe = FindRecipeById(&app->recipes, element.param1);
    RevertRecipe(&app->sim.inventory, recipe, &app->currentTime, &app->undoStack, &app->redoStack);
}

void RedoRecipeAction(Application *app, char action, StackElement element) {
    Tree* recipe = FindRecipeById(&app->recipes, element.param1);
    DoRecipe(&app->sim.inventory, recipe, &app->currentTime, &app->undoStack);
}

void ProcessUndo(Application* app) {
    if (IsStackEmpty(&app->undoStack)) {
        AddLogMessage("Nothing to undo! Undo stack is empty");
        PrintAppState(app);
        return;
    }

    char message[MAX_LOG_MESSAGE_LENGTH];
    StackElement element = StackPop(&app->undoStack);
    char action = element.action;
    int param1 = element.param1;
    int param2 = element.param2;

    switch (action) {
        case ACTION_MOVE_U:
        case ACTION_MOVE_R:
        case ACTION_MOVE_D:
        case ACTION_MOVE_L:
            char direction[10];
            element.param1 = GetX(&app->sim.position);
            element.param2 = GetY(&app->sim.position);
            SetSimulatorPosition(&app->sim, param1, param2);

            if (action == ACTION_MOVE_U) strcpy(direction, "up");
            if (action == ACTION_MOVE_R) strcpy(direction, "right");
            if (action == ACTION_MOVE_D) strcpy(direction, "down");
            if (action == ACTION_MOVE_L) strcpy(direction, "left");

            sprintf(message, "Undo move %s! Player moved back to (%d, %d)", direction, param1, param2);
            AddLogMessage(message);

            StackPush(&app->redoStack, element);
            break;

        case ACTION_WAIT:
            AddHour(&app->currentTime, -param1);
            AddMinute(&app->currentTime, -param2);

            char timeStr[32];
            TimeToString(&app->currentTime, timeStr);
            sprintf(message, "Undo wait! Time reverted back to %s", timeStr);
            AddLogMessage(message);

            AddMinute(&app->currentTime, 1); // Cancel out the -1 minute from the undo action
            break;

        case ACTION_MIX:
        case ACTION_CHOP:
        case ACTION_FRY:
        case ACTION_BOIL:
            UndoRecipeAction(app, action, element);
            break;

        case ACTION_BUY:
            FoodType* type = FindFoodTypeById(&app->foodDirectory, param1);
            RemoveLatestDeliveryQueue(&app->deliveryQueue, type);

            sprintf(message, "Undo buy! Order of %s has been cancelled", type->name);
            AddLogMessage(message);

            StackPush(&app->redoStack, element);
            break;

        default:
            break;
    }

    AddMinute(&app->currentTime, -1); // Undo action takes 1 minute
    PrintAppState(app);
}

void ProcessRedo(Application *app) {
    if (IsStackEmpty(&app->redoStack)) {
        AddLogMessage("Nothing to redo! Redo stack is empty");
        PrintAppState(app);
        return;
    }

    StackElement element = StackPop(&app->redoStack);
    char action = element.action;
    int param1 = element.param1;
    int param2 = element.param2;

    switch (action) {
        case ACTION_MOVE_U:
        case ACTION_MOVE_R:
        case ACTION_MOVE_D:
        case ACTION_MOVE_L:
            char direction[10];
            element.param1 = GetX(&app->sim.position);
            element.param2 = GetY(&app->sim.position);
            SetSimulatorPosition(&app->sim, param1, param2);

            if (action == ACTION_MOVE_U) strcpy(direction, "up");
            if (action == ACTION_MOVE_R) strcpy(direction, "right");
            if (action == ACTION_MOVE_D) strcpy(direction, "down");
            if (action == ACTION_MOVE_L) strcpy(direction, "left");

            sprintf(message, "Redo move %s! Player moved back to (%d, %d)", direction, param1, param2);
            AddLogMessage(message);

            StackPush(&app->undoStack, element);
            break;

        case ACTION_WAIT:
            AddLogMessage("Redo wait hasn't been implemented!");
            break;

        case ACTION_MIX:
        case ACTION_CHOP:
        case ACTION_FRY:
        case ACTION_BOIL:
            RedoRecipeAction(app, action, element);
            break;

        case ACTION_BUY:
            FoodType* type = FindFoodTypeById(&app->foodDirectory, param1);
            InsertDeliveryQueue(&app->deliveryQueue, type, &app->currentTime);

            sprintf(message, "Redo buy! Order of %s has been restored", type->name);
            AddLogMessage(message);

            StackPush(&app->undoStack, element);
            break;

        default:
            break;
    }
    
    PrintAppState(app);
}
