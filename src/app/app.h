#pragma once
#include "../base/boolean.h"
#include "../base/simulator.h"
#include "../adt/matrix.h"
#include "../adt/stack.h"

typedef struct {
    Simulator sim;
    Matrix map;
    Stack actions;
    bool isRunning;
    int iteration;
} Application;

void SplashScreen();
void GetName(char *name);
void InitApplication(Application *app, const char *configPath, const char *simName);

void ExecuteApplicationLoop(Application *app);

// char GetActionInput();
// void ProcessActionInput(char actions, Simulator *sim, Matrix *map);
// void PrintApplicationState(const Simulator *sim, const Matrix *map);