#include "../core/simulator.h"
#include "screen.h"
#include "strconst.h"
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
            
            char action = GetActionAtLocation(&app->map, i - 1, j - 1);
            if (action == ACTION_OBSTACLE) {
                printf("\033[1;30mX\033[0m ");
                continue;
            }

            printf("\033[1;32m");
            printf("%c ", GetSymbolForAction(GetActionAtLocation(&app->map, i - 1, j - 1)));
            printf("\033[0m");
        }

        printf("\n");
    }
}

void PrintInventory(const Application *app) {
    printf("\nInventory: Not Implemented\n");
}

void PrintCatalogMenu(const Application *app) {
    printf("\nCatalog: Not Implemented\n");
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