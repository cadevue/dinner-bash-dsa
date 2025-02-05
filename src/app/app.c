#include "app.h"
#include "../base/simulator.h"

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

void InitApplication(Application *app, const char *configPath, const char *simName) {
    ResetSimulator(&app->sim, simName, 0, 0);
    ResetMatrix(&app->map, 0, 0);
    ResetStack(&app->actions);

    app->isRunning = true;
    app->iteration = 0;

    PrintSimulatorInfo(&app->sim);
}

void ExecuteApplicationLoop(Application *app) {
    app->isRunning = false;
}