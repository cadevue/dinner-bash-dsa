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
bool IsValidName(const char *name);
void InitApplication(Application *app, const char *configPath);

void ExecuteApplicationLoop(Application *app);