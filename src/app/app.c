#include "app.h"
#include "screen.h"
#include "loader.h"
#include "strconst.h"
#include "../core/simulator.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_EQ(s1, s2) (strcasecmp(s1, s2) == 0)

void ClearAndPrintHeader() {
    ClearScreen();
    PrintHeader();
    
}

void PrintAppState(const Application *app) {
    ClearAndPrintHeader();
    PrintMap(app);
    printf("\n");
    PrintSimulatorInfo(&app->sim);
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

    printf("Registering user...\n", name);
    for (int i = 0; i <= 100; i += 2) {
        PrintProgressBar(i, 100);
        usleep(2000);
    }
}

bool IsValidName(const char *name) {
    return strlen(name) > 0;
}

bool IsSimulatorAt(const Simulator *sim, int x, int y) {
    return GetX(&sim->position) == x && GetY(&sim->position) == y;
}

void InitApplication(Application *app) {
    // Initialize the application
    ResetSimulator(&app->sim, 0, 0);
    ResetStack(&app->actions);

    /** Temporary hardcoded path */
    LoadFoodTypes(&app->foodDirectory, "../../config/basic/foods.txt");
    LoadRecipes(&app->recipes, "../../config/basic/recipes.txt");
    LoadMap(&app->map, &app->sim, "../../config/basic/map.txt");

    printf("\n\nLoading configurations...\n");
    for (int i = 0; i <= 100; i += 2) {
        PrintProgressBar(i, 100);
        usleep(5000);
    }
    printf("\nConfigurations loaded\n");

    printf("\nWelcome, %s!\n", app->sim.name);
    usleep(2000000);

    app->isRunning = true;
}

/** Command Implementor */
bool MoveSimulator(Application *app, int x, int y) {
    char action = GetActionAtLocation(&app->map, GetX(&app->sim.position), GetY(&app->sim.position));
    if (action == ACTION_OBSTACLE || action == ACTION_INVALID) {
        printf("You can't move there. There's a wall!\n");
        return false;
    } 
    
    if (action == ACTION_BUY || action == ACTION_MIX || action == ACTION_CHOP || action == ACTION_FRY || action == ACTION_BOIL) {
        printf("You can't move to tile action (%c)", GetSymbolForAction(action));
        return false;
    } 
    
    if (action == ACTION_NONE) {
        SetSimulatorPosition(&app->sim, x, y);
        printf("You moved to (%d, %d)\n", GetX(&app->sim.position), GetY(&app->sim.position));
        return true;
    }

    printf("You cannot move there!");
}

/** Command Processor */
static char command[50];
static bool shouldNextLoop = true;

void GetCommand(char *command) {
    printf("\nUse Command 'help' to see available commands!\n");
    printf("Enter command: ");
    fgets(command, 50, stdin);
    command[strlen(command) - 1] = '\0';
}

bool ProcessCommand(Application *app, char *command) {
    if (STR_EQ(command, "exit") || STR_EQ(command, "quit")) {
        app->isRunning = false;
        return true;
    } else if (STR_EQ(command, "help")) {
        ClearAndPrintHeader();
        PrintHelp();
        return false;
    } else if (STR_EQ(command, "back")) {
        PrintAppState(app);
        return false;
    } else if (STR_EQ(command, "legend")) {
        ClearAndPrintHeader();
        PrintLegend();
        return false;
    } else if (STR_EQ(command, "up") || STR_EQ(command, "down") || STR_EQ(command, "left") || STR_EQ(command, "right")) {
        int x = GetX(&app->sim.position);
        int y = GetY(&app->sim.position);

        bool success = false;

        if (STR_EQ(command, "up")) {
            success = MoveSimulator(app, x - 1, y);
        } else if (STR_EQ(command, "down")) {
            success = MoveSimulator(app, x + 1, y);
        } else if (STR_EQ(command, "left")) {
            success = MoveSimulator(app, x, y - 1);
        } else if (STR_EQ(command, "right")) {
            success = MoveSimulator(app, x, y + 1);
        }

        if (!success) {
            PrintAppState(app);
        }

        return success;
    } else {
        ClearAndPrintHeader();
        PrintMap(app);
        printf("\n");
        PrintSimulatorInfo(&app->sim);
        printf("\nUnknown command: %s\n", strlen(command) > 0 ? command : "<empty>");
        
        return false;
    }
}


void ExecuteApplicationLoop(Application *app) {
    ClearAndPrintHeader();
    PrintMap(app);
    printf("\n");
    PrintSimulatorInfo(&app->sim);

    // Command processing
    GetCommand(command);
    shouldNextLoop = ProcessCommand(app, command);

    while (!shouldNextLoop)
    {
        GetCommand(command);
        shouldNextLoop = ProcessCommand(app, command);
    }
}

void CleanUpApplication(Application *app) {
    FreeStaticList(&app->recipes);
    FreeSimulator(&app->sim);
}