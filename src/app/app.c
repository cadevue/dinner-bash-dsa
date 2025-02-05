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

void PrintProgressBar(int progress, int total) {
    const int barWidth = 50;
    float percentage = (float)progress / total;
    int filledWidth = barWidth * percentage;

    printf("[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\r", (int)(percentage * 100));
    fflush(stdout);  // Ensure the output is printed immediately
}

void RegisterUser(char *name) {
    ClearAndPrintHeader();

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
    for (int i = 0; i < 100; i += 2) {
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

    printf("\n\nLoading configurations...\n");
    for (int i = 0; i < 100; i += 2) {
        PrintProgressBar(i, 100);
        usleep(5000);
    }
    printf("\nConfigurations loaded\n");

    printf("\nWelcome, %s!\n", app->sim.name);
    usleep(2000000);

    app->isRunning = true;
}

void GetCommand(char *command) {
    printf("\nUse Command 'help' to see available commands\n");
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
        // Display the application
        ClearAndPrintHeader();
        PrintMap(app);
        printf("\n");
        PrintSimulatorInfo(&app->sim);

        // Command processing
        GetCommand(command);
        shouldNextLoop = ProcessCommand(app, command);

    } while (!shouldNextLoop);
}

void CleanUpApplication(Application *app) {
    FreeStaticList(&app->recipes);
    FreeSimulator(&app->sim);
}