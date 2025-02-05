#pragma once
#include "../base/boolean.h"
#include "../base/simulator.h"
#include "../adt/matrix.h"
#include "../adt/stack.h"
#include "../adt/static_list.h"

typedef struct {
    Simulator sim;
    Matrix map;
    Stack actions;
    StaticList foodDirectory;
    StaticList recipes;
    bool isRunning;
} Application;

void SplashScreen();
void GetName(char *name);
bool IsValidName(const char *name);
void InitApplication(Application *app, const char *configPath);

void ExecuteApplicationLoop(Application *app);