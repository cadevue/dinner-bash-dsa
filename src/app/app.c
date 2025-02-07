#include "app.h"
#include "screen.h"
#include "loader.h"
#include "strconst.h"
#include "../core/log.h"
#include "../core/action.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_EQ(s1, s2) (strcasecmp(s1, s2) == 0)
#define STR_START_WITH(s1, s2) (strncasecmp(s1, s2, strlen(s2)) == 0)

#define MAX_COMMAND_LEN 50
static char command[MAX_COMMAND_LEN];
static bool shouldNextLoop = true;

static char message[MAX_LOG_MESSAGE_LENGTH]; // shared free-to-use buffer for logging purposes

void ClearAndPrintHeader() {
    ClearScreen();
    PrintHeader();
}

void PrintAppState(const Application *app) {
    ClearAndPrintHeader();
    PrintTime(&app->currentTime);
    PrintMap(app);
    printf("\n");
    PrintSimulatorInfo(&app->sim);
    PrintOutLog();
}

void RegisterUser(char *name) {
    ClearAndPrintHeader();

    // Clear the input buffer
    printf("Enter your name: ");
    fgets(name, MAX_SIMULATOR_NAME_LEN, stdin);
    name[strlen(name) - 1] = '\0';

    while (!IsValidName(name)) {
        ClearAndPrintHeader();

        printf("Invalid name. Please try again.\n");
        printf("Enter your name: ");
        fgets(name, MAX_SIMULATOR_NAME_LEN, stdin);
        name[strlen(name) - 1] = '\0';
    }

    // printf("Registering user...\n", name);
    // for (int i = 0; i <= 100; i += 2) {
    //     PrintProgressBar(i, 100);
    //     usleep(2000);
    // }
}

bool IsValidName(const char *name) {
    return strlen(name) > 0;
}

void InitApplication(Application *app) {
    // Initialize the application
    ResetSimulator(&app->sim, 0, 0);
    ResetTime(&app->currentTime, 1, 8, 0);
    ResetDeliveryQueue(&app->deliveryQueue);
    ResetStack(&app->undoStack);
    ResetStack(&app->redoStack);

    /** Temporary hardcoded path */
    LoadFoodTypes(&app->foodDirectory, "../../config/basic/foods.txt");
    LoadRecipes(&app->recipes, &app->foodDirectory, "../../config/basic/recipes.txt");
    LoadMap(&app->map, &app->sim, "../../config/basic/map.txt");

    // printf("\n\nLoading configurations...\n");
    // for (int i = 0; i <= 100; i += 2) {
    //     PrintProgressBar(i, 100);
    //     usleep(5000);
    // }
    // printf("\nConfigurations loaded\n");

    // printf("\nWelcome, %s!\n", app->sim.name);
    // usleep(2000000);

    app->isRunning = true;
}

void UpdateApp(Application *app) {
    UpdateDeliveryQueue(&app->deliveryQueue, &app->sim.inventory, &app->currentTime);
    UpdateInventory(&app->sim.inventory, &app->currentTime);
}

/** Command Implementor */
bool MoveSimulator(Application *app, int x, int y, char *reason) {
    char action = GetElementAtLocation(&app->map, x, y);

    if (action == ACTION_OBSTACLE || action == ACTION_INVALID) {
        sprintf(reason, "You can't move there, there's a wall");
        return false;
    } 
    
    if (action == ACTION_BUY || action == ACTION_MIX || action == ACTION_CHOP || action == ACTION_FRY || action == ACTION_BOIL) {
        sprintf(reason, "You can't move to tile action (%c)", GetSymbolForAction(action));
        return false;
    } 
    
    if (action == ACTION_NONE) {
        SetSimulatorPosition(&app->sim, x, y);
        return true;
    }

    sprintf(reason, "Unknown action (%c)", GetSymbolForAction(action));
    return false;
}

bool IsAdjacentToActionTile(const Application *app, char action) {
    int x = GetX(&app->sim.position);
    int y = GetY(&app->sim.position);

    if (GetElementAtLocation(&app->map, x - 1, y) == action) return true;
    if (GetElementAtLocation(&app->map, x + 1, y) == action) return true;
    if (GetElementAtLocation(&app->map, x, y - 1) == action) return true;
    if (GetElementAtLocation(&app->map, x, y + 1) == action) return true;

    return false;
}

void PrintActionMenu(Application *app, char action) {
    switch (action) {
        case ACTION_MIX: PrintMixMenu(app); break;
        case ACTION_CHOP: PrintChopMenu(app); break;
        case ACTION_FRY: PrintFryMenu(app); break;
        case ACTION_BOIL: PrintBoilMenu(app); break;
        default: break;
    }
}

void GetCommand(char *command) {
    printf("\nUse Command 'help' to see available commands!\n");
    printf("Enter command: ");
    fgets(command, MAX_COMMAND_LEN, stdin);
    command[strlen(command) - 1] = '\0';
}

bool ExecuteRecipeAction(Application* app, char action) {
    ClearAndPrintHeader();
    PrintActionMenu(app, action);

    char internalCommand[MAX_COMMAND_LEN];
    bool success = false;

    int inputNum;
    Tree* recipes[STATIC_LIST_CAPACITY];
    int count = FindRecipesByAction(&app->recipes, action, recipes);

    while (!success) {
        GetCommand(internalCommand);

        if (sscanf(internalCommand, "%d", &inputNum) == 1) {
            if (inputNum > 0 && inputNum <= count) {
                Tree* recipe = recipes[inputNum - 1];

                success = DoRecipe(&app->sim.inventory, recipe, &app->currentTime, &app->undoStack);
                if (success) { 
                    StackPush(&app->undoStack, (StackElement) {action, inputNum, 0});
                    return true;
                }

                PrintAppState(app);
                return false;
            } else {
                ClearAndPrintHeader();
                PrintActionMenu(app, action);
                printf("\nInvalid index: %d, Choose between 1-%d\n", inputNum, count);
            }
        } else if (STR_EQ(internalCommand, "back")) {
            PrintAppState(app);
            return false;
        } else {
            ClearAndPrintHeader();
            PrintActionMenu(app, action);
            printf("\nInvalid menu command: %s\nType 'back' to return to the map\n", internalCommand);
        }
    }
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

    char direction[10];

    switch (action) {
        case ACTION_MOVE_U:
        case ACTION_MOVE_R:
        case ACTION_MOVE_D:
        case ACTION_MOVE_L:
            SetSimulatorPosition(&app->sim, param1, param2);

            if (action == ACTION_MOVE_U) strcpy(direction, "up");
            if (action == ACTION_MOVE_R) strcpy(direction, "right");
            if (action == ACTION_MOVE_D) strcpy(direction, "down");
            if (action == ACTION_MOVE_L) strcpy(direction, "left");

            sprintf(message, "Undo move %s! Player moved back to (%d, %d)", direction, param1, param2);
            AddLogMessage(message);
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

        case ACTION_USE_FOR_RECIPE:
            // RevertRecipe(&app->sim.inventory, &app->recipes, &app->currentTime, &app->undoStack, &app->redoStack);
            break;

        case ACTION_BUY:
            // RemoveDeliveryQueue(&app->deliveryQueue, param1);
            break;

        default:
            break;
    }

    StackPush(&app->redoStack, element);
    AddMinute(&app->currentTime, -1); // Undo action takes 1 minute
    PrintAppState(app);
}

/** Command Processor */
bool ProcessCommand(Application *app, char *command) {
    /** Exit */
    if (STR_EQ(command, "exit") || STR_EQ(command, "quit")) {
        app->isRunning = false;
        return true;

    /** Help */
    } else if (STR_EQ(command, "help")) {
        ClearAndPrintHeader();
        PrintHelp();
        return false;

    /** Back to game */
    } else if (STR_EQ(command, "back")) {
        PrintAppState(app);
        return false;

    /** Show Legend */
    } else if (STR_EQ(command, "legend")) {
        ClearAndPrintHeader();
        PrintLegend();
        return false;

    /** Navigation */
    } else if (
        STR_EQ(command, "up") || STR_EQ(command, "down") || STR_EQ(command, "left") || STR_EQ(command, "right") ||
        STR_EQ(command, "u") || STR_EQ(command, "d") || STR_EQ(command, "l") || STR_EQ(command, "r")
    ) {
        int x = GetX(&app->sim.position);
        int y = GetY(&app->sim.position);
        char reason[MAX_LOG_MESSAGE_LENGTH];
        char direction[10];
        char action = ACTION_INVALID;

        bool success = false;

        if (STR_EQ(command, "up") || STR_EQ(command, "u")) {
            success = MoveSimulator(app, x - 1, y, reason);
            strcpy(direction, "up");
            action = ACTION_MOVE_U;
        } else if (STR_EQ(command, "down") || STR_EQ(command, "d")) {
            success = MoveSimulator(app, x + 1, y, reason);
            strcpy(direction, "down");
            action = ACTION_MOVE_D;
        } else if (STR_EQ(command, "left") || STR_EQ(command, "l")) {
            success = MoveSimulator(app, x, y - 1, reason);
            strcpy(direction, "left");
            action = ACTION_MOVE_L;
        } else if (STR_EQ(command, "right") || STR_EQ(command, "r")) {
            success = MoveSimulator(app, x, y + 1, reason);
            strcpy(direction, "right");
            action = ACTION_MOVE_R;
        }

        if (!success) {
            sprintf(message, "Failed to move %s: %s", direction, reason);
            AddLogMessage(message);
            PrintAppState(app);
        } else {
            sprintf(message, "Player moved %s to (%d, %d)", direction, GetX(&app->sim.position), GetY(&app->sim.position));
            AddLogMessage(message);
            
            StackElement element = {action, x, y};
            StackPush(&app->undoStack, element);
        }

        return success;

    /** Wait */
    } else if (STR_START_WITH(command, "wait")) {
        int h, m;
        int result = sscanf(command + 5, "%d %d", &h, &m);
        if (result != 2) {
            PrintAppState(app);
            printf("\nInvalid wait parameters: %s\n", command + 5);
            return false;
        }

        if (h < 0 || m < 0) {
            PrintAppState(app);
            printf("\nInvalid wait parameters: %d %d\n", h, m);
            return false;
        }

        AddHour(&app->currentTime, h);
        AddMinute(&app->currentTime, m-1); // -1 because the loop will increment the time by 1 minute

        sprintf(message, "Player waited for %d hours and %d minutes", h, m);
        AddLogMessage(message);
        StackPush(&app->undoStack, (StackElement) {ACTION_WAIT, h, m});
        return true;

    /** Inventory */
    } else if (STR_EQ(command, "inventory")) {
        ClearAndPrintHeader();
        PrintInventory(app);
        return false;

    /** Catalog */
    } else if (STR_EQ(command, "catalog")) {
        ClearAndPrintHeader();
        PrintCatalog(app);
        return false;

    /** Recipe */
    } else if (STR_EQ(command, "cookbook")) {
        ClearAndPrintHeader();
        PrintCookbook(app);
        return false;

    /** Delivery */
    } else if (STR_EQ(command, "delivery")) {
        ClearAndPrintHeader();
        PrintDeliveryQueue(app);
        return false;

    /** Buy */
    } else if (STR_EQ(command, "buy")) {
        if (!IsAdjacentToActionTile(app, ACTION_BUY)) {
            AddLogMessage("Failed to buy: Not adjacent to telephone tile (T)");
            PrintAppState(app);
            return false;
        } else {
            ClearAndPrintHeader();
            PrintBuyMenu(app);

            char internalCommand[MAX_COMMAND_LEN];
            bool success = false;

            while (!success) {
                GetCommand(internalCommand);

                int inputNum;
                FoodType* types[STATIC_LIST_CAPACITY];
                int count = FindFoodTypesByAction(&app->foodDirectory, ACTION_BUY, types);

                if (sscanf(internalCommand, "%d", &inputNum) == 1) {
                    if (inputNum > 0 && inputNum <= count) {
                        FoodType* type = types[inputNum - 1];
                        InsertDeliveryQueue(&app->deliveryQueue, type, &app->currentTime);
                        
                        StackPush(&app->undoStack, (StackElement) {ACTION_BUY, type->id, 0});
                        return true;
                    } else {
                        ClearAndPrintHeader();
                        PrintBuyMenu(app);
                        printf("\nInvalid index: %d, Choose between 1-%d\n", inputNum, count);
                    }
                } else if (STR_EQ(internalCommand, "back")) {
                    PrintAppState(app);
                    return false;
                } else {
                    ClearAndPrintHeader();
                    PrintBuyMenu(app);
                    printf("\nInvalid menu command: %s\nType 'back' to return to the map\n", internalCommand);
                }
            }
        }
    /** Mix */
    } else if (STR_EQ(command, "mix")) {
        if (!IsAdjacentToActionTile(app, ACTION_MIX)) {
            AddLogMessage("Failed to mix: Not adjacent to mixing tile (M)");
            PrintAppState(app);
            return false;
        } else {
            return ExecuteRecipeAction(app, ACTION_MIX);
        }

    /** Chop */
    } else if (STR_EQ(command, "chop")) {
        if (!IsAdjacentToActionTile(app, ACTION_CHOP)) {
            AddLogMessage("Failed to chop: Not adjacent to chopping tile (C)");
            PrintAppState(app);
            return false;
        } else {
            return ExecuteRecipeAction(app, ACTION_CHOP);
        }
    /** Fry */
    } else if (STR_EQ(command, "fry")) {
        if (!IsAdjacentToActionTile(app, ACTION_FRY)) {
            AddLogMessage("Failed to fry: Not adjacent to frying tile (F)");
            PrintAppState(app);
            return false;
        } else {
            return ExecuteRecipeAction(app, ACTION_FRY);
        }
        
        return false;

    /** Boil */
    } else if (STR_EQ(command, "boil")) {
        if (!IsAdjacentToActionTile(app, ACTION_BOIL)) {
            AddLogMessage("Failed to boil: Not adjacent to boiling tile (B)");
            PrintAppState(app);
            return false;
        } else {
            return ExecuteRecipeAction(app, ACTION_BOIL);
        }

        return false;

    /** Undo */
    } else if (STR_EQ(command, "undo")) {
        ProcessUndo(app);
        return false;

    /** Unknown command */
    } else {
        sprintf(message, "Unknown command: %s", strlen(command) > 0 ? command : "<empty>");
        AddLogMessage(message);
        PrintAppState(app);
        
        return false;
    }
}

void ExecuteApplicationLoop(Application *app) {
    UpdateApp(app);
    PrintAppState(app);

    // Command processing
    do {
        GetCommand(command);
        shouldNextLoop = ProcessCommand(app, command);
    } while (!shouldNextLoop);

    AddMinute(&app->currentTime, 1); // Increment time by 1 minute for each execution loop
}

void CleanUpApplication(Application *app) {
    FreeStaticList(&app->recipes);
    FreeSimulator(&app->sim);
    FreeDeliveryQueue(&app->deliveryQueue);
}