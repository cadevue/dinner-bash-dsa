#pragma once

#include "../core/boolean.h"
#include "../core/simulator.h"
#include "../core/time.h"
#include "../core/log.h"
#include "../adt/matrix.h"
#include "../adt/stack.h"
#include "../adt/static_list.h"

typedef struct {
    // Application State
    Simulator sim;
    Matrix map;
    Time currentTime;
    bool isRunning;

    // Collections
    StaticList foodDirectory;
    StaticList recipes;
    
    // Utilities
    Stack actions;
    Log log;
} Application;

void PrintSplashScreen();
void RegisterUser(char *name);
bool IsValidName(const char *name);
void InitApplication(Application *app);

void ExecuteApplicationLoop(Application *app);
void CleanUpApplication(Application *app);