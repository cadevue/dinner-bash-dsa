#include <stdio.h>
#include <string.h>
#include "simulator.h"

void ResetSimulator(Simulator *sim, int x, int y) {
    ResetPoint(&sim->position, x, y);
    ResetInventory(&sim->inventory);
}

void SetSimulatorName(Simulator *sim, const char *name) {
    strcpy(sim->name, name);
}

const char *GetSimulatorName(const Simulator *sim){ 
    return sim->name;
}

void SetSimulatorPosition(Simulator *sim, int x, int y) {
    ResetPoint(&sim->position, x, y);
}

Point GetSimulatorPosition(const Simulator *sim) {
    return sim->position;
}

void PrintSimulatorInfo(const Simulator *sim) {
    printf("Player: %s\n", sim->name);
    printf("Position: (%d, %d)\n", GetX(&sim->position), GetY(&sim->position));
}

void FreeSimulator(Simulator *sim) {
    FreeInventory(&sim->inventory);
}