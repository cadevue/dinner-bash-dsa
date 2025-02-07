#include <stdio.h>
#include "./app/app.h"
#include "./app/screen.h"
#include "./core/log.h"

int main ()
{
    Application app;

    ClearScreen();
    PrintSplashScreen();

    RegisterUser(app.sim.name);

    ResetLog(&GlobalLog);
    InitApplication(&app);

    AddLogMessage("Welcome to Dinner Bash");

    while (app.isRunning) {
        ExecuteApplicationLoop(&app);
    }

    CleanUpApplication(&app);

    printf("\nApplication exitted gracefully\n");
    return 0;
}
