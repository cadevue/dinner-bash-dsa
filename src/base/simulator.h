#pragma once

#include "point.h"
#define MAX_SIMULATOR_NAME_LEN 50

typedef struct {
    char name[MAX_SIMULATOR_NAME_LEN];
    Point position;
    // Inventory inventory;
} Simulator;

void SetSimulatorName(Simulator *sim, const char *name);
const char *GetSimulatorName(const Simulator *sim);
void PrintSimulatorInfo(const Simulator *sim);