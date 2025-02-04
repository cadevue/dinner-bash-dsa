#include <stdio.h>
#include <string.h>
#include "simulator.h"

void SetSimulatorName(Simulator *sim, const char *name) {
    strcpy(sim->name, name);
}

const char *GetSimulatorName(const Simulator *sim){ 
    return sim->name;
}

void PrintSimulatorInfo(const Simulator *sim) {
    printf("Simulator: %s\n", sim->name);
    printf("Position: (%d, %d)\n", GetX(&sim->position), GetY(&sim->position));
}