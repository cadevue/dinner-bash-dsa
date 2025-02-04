#include <stdio.h>
#include "./base/point.h"
#include "./base/simulator.h"

int main ()
{
    printf("Application Started!\n");

    Simulator sim = {
        .name = "BNMO Application",
        .position = {0, 0}
    };
    PrintSimulatorInfo(&sim);

    return 0;
}
