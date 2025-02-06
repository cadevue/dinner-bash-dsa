#pragma once

#include "../core/boolean.h"
#include "../core/simulator.h"
#include "../core/time.h"
#include "../adt/matrix.h"
#include "../adt/stack.h"
#include "../adt/static_list.h"

typedef struct {
    Simulator sim;
    Matrix map;
    Stack actions;
    StaticList foodDirectory;
    StaticList recipes;
    Time currentTime;
    bool isRunning;
} Application;

void PrintSplashScreen();
void RegisterUser(char *name);
bool IsValidName(const char *name);
void InitApplication(Application *app);

void ExecuteApplicationLoop(Application *app);
void CleanUpApplication(Application *app);