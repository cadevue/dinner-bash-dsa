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

void PrintInventory(const Application *app);
void PrintCatalogMenu(const Application *app);
void PrintCookbookMenu(const Application *app);
void PrintDeliveryMenu(const Application *app);

void PrintBuyMenu(const Application *app);
void PrintMixMenu(const Application *app);
void PrintChopMenu(const Application *app);
void PrintFryMenu(const Application *app);
void PrintBoilMenu(const Application *app);