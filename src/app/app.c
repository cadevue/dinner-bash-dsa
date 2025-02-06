#include "app.h"
#include "screen.h"
#include "loader.h"
#include "strconst.h"

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define STR_EQ(s1, s2) (strcasecmp(s1, s2) == 0)
#define STR_START_WITH(s1, s2) (strncasecmp(s1, s2, strlen(s2)) == 0)

void ClearAndPrintHeader() {
    ClearScreen();
    PrintHeader();
}

void PrintAppState(const Application *app) {
    ClearAndPrintHeader();
    PrintTime(&app->currentTime);
    PrintMap(app);
    printf("\n");
    PrintSimulatorInfo(&app->sim);
}

void RegisterUser(char *name) {
    ClearAndPrintHeader();

    // Clear the input buffer
    printf("Enter your name: ");
    fgets(name, MAX_SIMULATOR_NAME_LEN, stdin);
    name[strlen(name) - 1] = '\0';

    while (!IsValidName(name)) {
        ClearAndPrintHeader();

        printf("Invalid name. Please try again.\n");
        printf("Enter your name: ");
        fgets(name, MAX_SIMULATOR_NAME_LEN, stdin);
        name[strlen(name) - 1] = '\0';
    }

    // printf("Registering user...\n", name);
    // for (int i = 0; i <= 100; i += 2) {
    //     PrintProgressBar(i, 100);
    //     usleep(2000);
    // }
}

bool IsValidName(const char *name) {
    return strlen(name) > 0;
}

void InitApplication(Application *app) {
    // Initialize the application
    ResetSimulator(&app->sim, 0, 0);
    ResetStack(&app->actions);
    ResetTime(&app->currentTime, 1, 8, 0);

    /** Temporary hardcoded path */
    LoadFoodTypes(&app->foodDirectory, "../../config/basic/foods.txt");
    LoadRecipes(&app->recipes, "../../config/basic/recipes.txt");
    LoadMap(&app->map, &app->sim, "../../config/basic/map.txt");

    // printf("\n\nLoading configurations...\n");
    // for (int i = 0; i <= 100; i += 2) {
    //     PrintProgressBar(i, 100);
    //     usleep(5000);
    // }
    // printf("\nConfigurations loaded\n");

    printf("\nWelcome, %s!\n", app->sim.name);
    usleep(100000);
    // usleep(2000000);

    app->isRunning = true;
}

/** Command Implementor */
bool MoveSimulator(Application *app, int x, int y, char *reason) {
    char action = GetActionAtLocation(&app->map, x, y);

    if (action == ACTION_OBSTACLE || action == ACTION_INVALID) {
        sprintf(reason, "You can't move there, there's a wall");
        return false;
    } 
    
    if (action == ACTION_BUY || action == ACTION_MIX || action == ACTION_CHOP || action == ACTION_FRY || action == ACTION_BOIL) {
        sprintf(reason, "You can't move to tile action (%c)", GetSymbolForAction(action));
        return false;
    } 
    
    if (action == ACTION_NONE) {
        SetSimulatorPosition(&app->sim, x, y);
        return true;
    }

    sprintf(reason, "Unknown action (%c)", GetSymbolForAction(action));
    return false;
}

/** Command Processor */
static char command[50];
static bool shouldNextLoop = true;

void GetCommand(char *command) {
    printf("\nUse Command 'help' to see available commands!\n");
    printf("Enter command: ");
    fgets(command, 50, stdin);
    command[strlen(command) - 1] = '\0';
}

bool ProcessCommand(Application *app, char *command) {
    /** Exit */
    if (STR_EQ(command, "exit") || STR_EQ(command, "quit")) {
        app->isRunning = false;
        return true;

    /** Help */
    } else if (STR_EQ(command, "help")) {
        ClearAndPrintHeader();
        PrintHelp();
        return false;

    /** Back to game */
    } else if (STR_EQ(command, "back")) {
        PrintAppState(app);
        return false;

    /** Show Legend */
    } else if (STR_EQ(command, "legend")) {
        ClearAndPrintHeader();
        PrintLegend();
        return false;

    /** Navigation */
    } else if (
        STR_EQ(command, "up") || STR_EQ(command, "down") || STR_EQ(command, "left") || STR_EQ(command, "right") ||
        STR_EQ(command, "u") || STR_EQ(command, "d") || STR_EQ(command, "l") || STR_EQ(command, "r")
    ) {
        int x = GetX(&app->sim.position);
        int y = GetY(&app->sim.position);
        char reason[120];

        bool success = false;

        if (STR_EQ(command, "up") || STR_EQ(command, "u")) {
            success = MoveSimulator(app, x - 1, y, reason);
        } else if (STR_EQ(command, "down") || STR_EQ(command, "d")) {
            success = MoveSimulator(app, x + 1, y, reason);
        } else if (STR_EQ(command, "left") || STR_EQ(command, "l")) {
            success = MoveSimulator(app, x, y - 1, reason);
        } else if (STR_EQ(command, "right") || STR_EQ(command, "r")) {
            success = MoveSimulator(app, x, y + 1, reason);
        }

        if (!success) {
            PrintAppState(app);
            printf("\n%s\n", reason);
        }

        return success;

    /** Wait */
    } else if (STR_START_WITH(command, "wait")) {
        int h, m;
        int result = sscanf(command + 5, "%d %d", &h, &m);
        if (result != 2) {
            PrintAppState(app);
            printf("\nInvalid wait parameters: %s\n", command + 5);
            return false;
        }

        if (h < 0 || m < 0) {
            PrintAppState(app);
            printf("\nInvalid wait parameters: %d %d\n", h, m);
            return false;
        }

        AddHour(&app->currentTime, h);
        AddMinute(&app->currentTime, m-1); // -1 because the loop will increment the time by 1 minute
        return true;

    /** Inventory */
    } else if (STR_EQ(command, "inventory")) {
        PrintAppState(app);
        PrintInventory(app);
        return false;

    /** Catalog */
    } else if (STR_EQ(command, "catalog")) {
        PrintAppState(app);
        PrintCatalogMenu(app);
        return false;

    /** Recipe */
    } else if (STR_EQ(command, "cookbook")) {
        PrintAppState(app);
        PrintCookbookMenu(app);
        return false;

    /** Delivery */
    } else if (STR_EQ(command, "delivery")) {
        PrintAppState(app);
        PrintDeliveryMenu(app);
        return false;

    /** Buy */
    } else if (STR_EQ(command, "buy")) {
        PrintBuyMenu(app);
        return false;

    /** Mix */
    } else if (STR_EQ(command, "mix")) {
        PrintAppState(app);
        PrintMixMenu(app);
        return false;

    /** Chop */
    } else if (STR_EQ(command, "chop")) {
        PrintAppState(app);
        PrintChopMenu(app);
        return false;

    /** Fry */
    } else if (STR_EQ(command, "fry")) {
        PrintAppState(app);
        PrintFryMenu(app);
        return false;

    /** Boil */
    } else if (STR_EQ(command, "boil")) {
        PrintAppState(app);
        PrintBoilMenu(app);
        return false;

    /** Unknown command */
    } else {
        PrintAppState(app);
        printf("\nUnknown command: %s\n", strlen(command) > 0 ? command : "<empty>");
        
        return false;
    }
}


void ExecuteApplicationLoop(Application *app) {
    PrintAppState(app);

    // Command processing
    do {
        GetCommand(command);
        shouldNextLoop = ProcessCommand(app, command);
    } while (!shouldNextLoop);

    AddMinute(&app->currentTime, 1); // Increment time by 1 minute for each execution loop
}

void CleanUpApplication(Application *app) {
    FreeStaticList(&app->recipes);
    FreeSimulator(&app->sim);
}