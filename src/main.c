#include <stdio.h>
#include "./base/point.h"
#include "./base/simulator.h"
#include "./adt/matrix.h"
#include "./adt/static_list.h"

int main ()
{
    printf("Application Started!\n");

    // Load the application
    // Food & Recipes
    // StaticList foodTypes;
    // LoadFoodTypes(&foodTypes);

    // StaticList recipes;
    // LoadRecipes(&recipes);

    // This should be loaded based on configuration
    /** Apllication State */
    // Simulator
    Simulator sim;
    ResetSimulator(&sim, "BNMO Simulator", 0, 0);
    PrintSimulatorInfo(&sim);

    // Map
    // Matrix map;
    // LoadMap(&map);

    // Application Loop

    return 0;
}
