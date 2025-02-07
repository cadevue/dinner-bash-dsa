#pragma once
#include "app.h"

// Static
void ClearScreen();
void PrintSplashScreen();
void PrintHeader();
void PrintHelp();
void PrintLegend();
void PrintProgressBar(int progress, int total);

// Dynamic
void PrintMap(const Application *app);

void PrintInventory(Application *app);
void PrintCatalogMenu(Application *app);
void PrintCookbookMenu(Application *app);
void PrintDeliveryMenu(Application *app);

void PrintBuyMenu(const Application *app);
void PrintMixMenu(const Application *app);
void PrintChopMenu(const Application *app);
void PrintFryMenu(const Application *app);
void PrintBoilMenu(const Application *app);