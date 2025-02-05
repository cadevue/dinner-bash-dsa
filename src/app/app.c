#include "app.h"
#include "loader.h"
#include "../core/simulator.h"

#include <stdio.h>
#include <string.h>

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

void PrintMap(const Application *app) {
    for (int i = 0; i < app->map.rowEff + 2; i++) {
        for (int j = 0; j < app->map.colEff + 2; j++) {
            if (i == 0 || i == app->map.rowEff + 1 || j == 0 || j == app->map.colEff + 1) {
                printf("* ");
                continue;
            }

            printf("%c ", GetSymbolForAction(GetActionAtLocation(&app->map, i - 1, j - 1)));
        }

        printf("\n");
    }
}

void InitApplication(Application *app, const char *configPath) {
    printf("Loading configuration: %s\n", configPath);

    // Initialize the application
    ResetSimulator(&app->sim, 0, 0);
    ResetStack(&app->actions);

    // Load the configuration
    LoadFoodTypes(&app->foodDirectory, "food_types.json");
    LoadRecipes(&app->recipes, "recipes.json");
    LoadMap(&app->map, "map.json");

    app->isRunning = true;
    PrintSimulatorInfo(&app->sim);
    PrintMap(app);
}

void ExecuteApplicationLoop(Application *app) {
    app->isRunning = false;
}