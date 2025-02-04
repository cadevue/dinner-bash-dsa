#include <stdio.h>
#include "./base/point.h"
#include "./base/simulator.h"

int main ()
{
    printf("Application Started!\n");

    // Load the application

    // Load Arena
    // Load list of food
    // Load list of recipes

    // This should be loadede based on configuration
    Simulator sim;
    ResetSimulator(&sim, "BNMO Simulator", 0, 0);
    PrintSimulatorInfo(&sim);

    return 0;
}
