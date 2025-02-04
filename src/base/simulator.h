#pragma once
#include "point.h"
#include "../adt/prio_queue.h"

#define MAX_SIMULATOR_NAME_LEN 50

typedef struct {
    char name[MAX_SIMULATOR_NAME_LEN];
    Point position;
    PrioQueue inventory;
} Simulator;

void ResetSimulator(Simulator *sim, const char *name, int x, int y);

void SetSimulatorName(Simulator *sim, const char *name);
const char *GetSimulatorName(const Simulator *sim);
void PrintSimulatorInfo(const Simulator *sim);