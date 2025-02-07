#include "../core/simulator.h"
#include "../core/action.h"
#include "../adt/static_list.h"
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


void PrintInventory(Application *app) {
    printf("\nInventory: Not Implemented\n");
}

#define BOX_WIDTH 48
#define BOX_TOP            "<------------------------------------------------->"
#define BOX_MIDDLE         "|                                                 |"
#define BOX_BOTTOM         "<------------------------------------------------->"

#define CATALOG_HEADER     "|==================== \033[1mCATALOG\033[0m ====================|"
#define RECIPE_HEADER      "|==================== \033[1mCOOKBOOK\033[0m ===================|"

void FormatCatalogItem(const FoodType* foodType) {
    char nameLine[BOX_WIDTH * 2] ;
    char timeExpireLine[BOX_WIDTH * 2];
    char timeDeliverLine[BOX_WIDTH * 2];
    char acquireLine[BOX_WIDTH * 2];

    char buffer[BOX_WIDTH * 2];

    // Name
    int nameLen = strlen(foodType->name);
    snprintf(nameLine, BOX_WIDTH * 2, "| \033[1;33m%s\033[0m%-*s |", foodType->name, BOX_WIDTH - nameLen - 1, "");

    // Time to Expire
    DurationToString(&foodType->timeToExpire, buffer);
    int timeExpireLen = strlen(buffer);
    snprintf(timeExpireLine, BOX_WIDTH * 2, "| Time to Expire: %s%-*s |", buffer, BOX_WIDTH - timeExpireLen - 17, "");

    // Time to Deliver
    DurationToString(&foodType->timeToDeliver, buffer);
    int timeDeliverLen = strlen(buffer);
    snprintf(timeDeliverLine, BOX_WIDTH * 2, "| Time to Deliver: %s%-*s |", buffer, BOX_WIDTH - timeDeliverLen - 18, "");

    // To Acquire
    GetActionName(foodType->actionType, buffer);
    int acquireLen = strlen(buffer);
    snprintf(acquireLine, BOX_WIDTH * 2, "| To Acquire: \033[1;32m%s\033[0m%-*s |", buffer, BOX_WIDTH - acquireLen - 13, "");

    printf("%s\n", BOX_TOP);
    printf("%s\n", nameLine);
    printf("%s\n", timeExpireLine);
    printf("%s\n", timeDeliverLine);
    printf("%s\n", BOX_MIDDLE);
    printf("%s\n", acquireLine);
    printf("%s\n", BOX_BOTTOM);
}

void PrintCatalogMenu(Application *app) {
    printf("%s\n", BOX_TOP);
    printf("%s\n", CATALOG_HEADER);
    for (int i = 0; i < app->foodDirectory.count; i++) {
        FormatCatalogItem(&GetStaticListElement(&app->foodDirectory, i)->foodType);
    }
    printf("\ntype 'back' to return to the game\n");
}

void FormatCookbookItem(Tree *recipe, StaticList *foodDirectory) {
    char nameLine[BOX_WIDTH * 2];
    char ingredientLines[BOX_WIDTH * 2 * MAX_TREE_CHILD_COUNT];
    char actionLine[BOX_WIDTH * 2];
    char buffer[BOX_WIDTH * 2];

    // Name
    FoodType *foodType = FindFoodTypeById(foodDirectory, recipe->data);
    int nameLen = strlen(foodType->name);
    snprintf(nameLine, BOX_WIDTH * 2, "| \033[1;33m%s\033[0m%-*s |", foodType->name, BOX_WIDTH - nameLen - 1, "");

    // Ingredients
    char *ingredientLine = ingredientLines;
    for (int i = 0; i < recipe->childCount; i++) {
        FoodType *ingredient = FindFoodTypeById(foodDirectory, GetChild(recipe, i)->data);
        strcpy(buffer, ingredient->name);
        int bufferLen = strlen(buffer);
        snprintf(ingredientLine, BOX_WIDTH * 2, "|     - %s%-*s |", buffer, BOX_WIDTH - bufferLen - 7, "");
        ingredientLine += BOX_WIDTH * 2;
    }

    // Action
    GetActionName(foodType->actionType, buffer);
    int actionLen = strlen(buffer);
    snprintf(actionLine, BOX_WIDTH * 2, "| Action: \033[1;32m%s\033[0m%-*s |", buffer, BOX_WIDTH - actionLen - 9, "");

    printf("%s\n", BOX_TOP);
    printf("%s\n", nameLine);
    printf("%s\n", BOX_MIDDLE);
    printf("| Ingredients:                                    |\n");
    for (int i = 0; i < recipe->childCount; i++) {
        printf("%s\n", ingredientLines + i * BOX_WIDTH * 2);
    }
    printf("%s\n", BOX_MIDDLE);
    printf("%s\n", actionLine);
    printf("%s\n", BOX_BOTTOM);
}

void PrintCookbookMenu(Application *app) {
    printf("%s\n", BOX_TOP);
    printf("%s\n", RECIPE_HEADER);
    for (int i = 0; i < app->recipes.count; i++) {
        Tree *recipe = (Tree *)GetStaticListElement(&app->recipes, i)->recipe;
        if (recipe->childCount != 0) {
            FormatCookbookItem(recipe, &app->foodDirectory);
        }
    }
    printf("\ntype 'back' to return to the game\n");
}

void PrintDeliveryMenu(Application *app) {
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