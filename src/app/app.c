#include "app.h"
#include "loader.h"
#include "../core/simulator.h"

#include <stdio.h>
#include <string.h>

#define STR_EQ(s1, s2) (strcasecmp(s1, s2) == 0)

void ClearScreen() {
    printf("\033[H\033[J");
}

void SplashScreen() {
    printf("Welcome to BNMO Simulator\n");
    printf("Press any key to continue...\n");
    getchar();
}

void GetName(char *name) {
    printf("Enter your name: ");
    fgets(name, MAX_SIMULATOR_NAME_LEN, stdin);
    name[strlen(name) - 1] = '\0';
}

bool IsValidName(const char *name) {
    return strlen(name) > 0;
}

bool IsSimulatorAt(const Simulator *sim, int x, int y) {
    return GetX(&sim->position) == x && GetY(&sim->position) == y;
}

void PrintMap(const Application *app) {
    for (int i = 0; i < app->map.rowEff + 2; i++) {
        for (int j = 0; j < app->map.colEff + 2; j++) {
            if (i == 0 || i == app->map.rowEff + 1 || j == 0 || j == app->map.colEff + 1) {
                printf("* ");
                continue;
            } else if (IsSimulatorAt(&app->sim, i - 1, j - 1)) {
                printf("S ");
                continue;
            }

            printf("%c ", GetSymbolForAction(GetActionAtLocation(&app->map, i - 1, j - 1)));
        }

        printf("\n");
    }
}

void InitApplication(Application *app) {
    // Initialize the application
    ResetSimulator(&app->sim, 0, 0);
    ResetStack(&app->actions);

    /** Temporary hardcoded path */
    LoadFoodTypes(&app->foodDirectory, "../../config/basic/foods.txt");
    LoadRecipes(&app->recipes, "../../config/basic/recipes.txt");
    LoadMap(&app->map, &app->sim, "../../config/basic/map.txt");

    app->isRunning = true;
}

void GetCommand(char *command) {
    printf("Enter command: ");
    fgets(command, 50, stdin);
    command[strlen(command) - 1] = '\0';
}

bool ProcessCommand(Application *app, char *command) {
    if (STR_EQ(command, "exit") || STR_EQ(command, "quit")) {
        app->isRunning = false;
        return true;
    } else {
        printf("Unknown command\n");
        return true;
    }
}

static char command[50];
static bool shouldNextLoop = true;

void ExecuteApplicationLoop(Application *app) {
    do {
        ClearScreen();
        PrintSimulatorInfo(&app->sim);
        PrintMap(app);
        GetCommand(command);
        shouldNextLoop = ProcessCommand(app, command);
    } while (!shouldNextLoop);
}

void CleanUpApplication(Application *app) {
    FreeStaticList(&app->recipes);
    FreeSimulator(&app->sim);
}