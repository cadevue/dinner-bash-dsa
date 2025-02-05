#include <stdio.h>
#include "./app/app.h"

int main ()
{
    Application app;

    SplashScreen();

    GetName(app.sim.name);
    while (!IsValidName(app.sim.name)) {
        printf("Invalid name. Please enter a valid name.\n");
        GetName(app.sim.name);
    }

    InitApplication(&app);

    while (app.isRunning) {
        ExecuteApplicationLoop(&app);
    }

    CleanUpApplication(&app);

    printf("Application exit gracefully\n");
    return 0;
}
