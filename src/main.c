#include <stdio.h>
#include "./app/app.h"
#include "./app/screen.h"

int main ()
{
    Application app;

    ClearScreen();
    PrintSplashScreen();

    RegisterUser(app.sim.name);

    InitApplication(&app);

    while (app.isRunning) {
        ExecuteApplicationLoop(&app);
    }

    CleanUpApplication(&app);

    printf("\n\nApplication exit gracefully\n");
    return 0;
}
