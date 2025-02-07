#include "../core/simulator.h"
#include "screen.h"
#include "strconst.h"
#include "../core/action.h"
#include <stdio.h>
#include <string.h>

void ClearScreen() {
    printf("\033[H\033[J");
}

void PrintSplashScreen() {
    printf("%s", SPLASH_SCREEN);
    printf("     ");
    while (getchar() != '\n');
}

void PrintHeader() {
    printf("%s", HEADER);
}

void PrintHelp() {
    printf("%s", HELP_COMMANDS);
}

void PrintLegend() {
    printf("%s", LEGEND);
}

void PrintProgressBar(int progress, int total) {
    const int barWidth = 50;
    float percentage = (float)progress / total;
    int filledWidth = barWidth * percentage;

    printf("[");
    for (int i = 0; i < barWidth; ++i) {
        if (i < filledWidth) {
            printf("=");
        } else {
            printf(" ");
        }
    }
    printf("] %d%%\r", (int)(percentage * 100));
    fflush(stdout);  // Ensure the output is printed immediately
}

bool IsSimulatorAt(const Simulator *sim, int x, int y) {
    return GetX(&sim->position) == x && GetY(&sim->position) == y;
}


void PrintMap(const Application *app) {
    for (int i = 0; i < app->map.rowEff + 2; i++) {
        for (int j = 0; j < app->map.colEff + 2; j++) {
            if (i == 0 || i == app->map.rowEff + 1 || j == 0 || j == app->map.colEff + 1) {
                printf("* ");
                continue;
            } else if (IsSimulatorAt(&app->sim, i - 1, j - 1)) {
                printf("\033[1;31m@\033[0m ");
                continue;
            }
            
            char action = GetElementAtLocation(&app->map, i - 1, j - 1);
            if (action == ACTION_OBSTACLE) {
                printf("\033[1;30mX\033[0m ");
                continue;
            }

            printf("\033[1;32m");
            printf("%c ", GetSymbolForAction(GetElementAtLocation(&app->map, i - 1, j - 1)));
            printf("\033[0m");
        }

        printf("\n");
    }
}


void PrintInventory(const Application *app) {
    printf("\nInventory: Not Implemented\n");
}

#define CATALOG_BOX_WIDTH 48
#define CATALOG_HEADER     "|==================== \033[1mCATALOG\033[0m ====================|"
#define CATALOG_BOX_TOP    "<------------------------------------------------->"
#define CATALOG_BOX_MIDDLE "|                                                 |"
#define CATALOG_BOX_BOTTOM "<------------------------------------------------->"
void FormatCatalogItem(const FoodType* foodType) {
    char nameLine[CATALOG_BOX_WIDTH * 2] ;
    char timeExpireLine[CATALOG_BOX_WIDTH * 2];
    char timeDeliverLine[CATALOG_BOX_WIDTH * 2];
    char acquireLine[CATALOG_BOX_WIDTH * 2];

    char buffer[CATALOG_BOX_WIDTH * 2];

    // Name
    int nameLen = strlen(foodType->name);
    snprintf(nameLine, CATALOG_BOX_WIDTH * 2, "| \033[1;33m%s\033[0m%-*s |", foodType->name, CATALOG_BOX_WIDTH - nameLen - 1, "");

    // Time to Expire
    DurationToString(&foodType->timeToExpire, buffer);
    int timeExpireLen = strlen(buffer);
    snprintf(timeExpireLine, CATALOG_BOX_WIDTH * 2, "| Time to Expire: %s%-*s |", buffer, CATALOG_BOX_WIDTH - timeExpireLen - 17, "");

    // Time to Deliver
    DurationToString(&foodType->timeToDeliver, buffer);
    int timeDeliverLen = strlen(buffer);
    snprintf(timeDeliverLine, CATALOG_BOX_WIDTH * 2, "| Time to Deliver: %s%-*s |", buffer, CATALOG_BOX_WIDTH - timeDeliverLen - 18, "");

    // To Acquire
    GetActionName(foodType->actionType, buffer);
    int acquireLen = strlen(buffer);
    snprintf(acquireLine, CATALOG_BOX_WIDTH * 2, "| To Acquire: \033[1;32m%s\033[0m%-*s |", buffer, CATALOG_BOX_WIDTH - acquireLen - 13, "");

    printf("%s\n", CATALOG_BOX_TOP);
    printf("%s\n", nameLine);
    printf("%s\n", timeExpireLine);
    printf("%s\n", timeDeliverLine);
    printf("%s\n", CATALOG_BOX_MIDDLE);
    printf("%s\n", acquireLine);
    printf("%s\n", CATALOG_BOX_BOTTOM);
}

void PrintCatalogMenu(Application *app) {
    printf("%s\n", CATALOG_BOX_TOP);
    printf("%s\n", CATALOG_HEADER);
    for (int i = 0; i < app->foodDirectory.count; i++) {
        FormatCatalogItem(&GetStaticListElement(&app->foodDirectory, i)->foodType);
    }
    printf("\ntype 'back' to return to the game\n");
}

void PrintCookbookMenu(const Application *app) {
    printf("\nCookbook: Not Implemented\n");
}

void PrintDeliveryMenu(const Application *app) {
    printf("\nDelivery: Not Implemented\n");
}

void PrintBuyMenu(const Application *app) {
    printf("\nBuy: Not Implemented\n");
}

void PrintMixMenu(const Application *app) {
    printf("\nMix: Not Implemented\n");
}

void PrintChopMenu(const Application *app) {
    printf("\nChop: Not Implemented\n");
}

void PrintFryMenu(const Application *app) {
    printf("\nFry: Not Implemented\n");
}

void PrintBoilMenu(const Application *app) {
    printf("\nBoil: Not Implemented\n");
}