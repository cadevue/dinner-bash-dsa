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
void PrintCatalog(Application *app);
void PrintCookbook(Application *app);
void PrintDeliveryQueue(Application *app);

void PrintBuyMenu(Application *app);
void PrintMixMenu(Application *app);
void PrintChopMenu(Application *app);
void PrintFryMenu(Application *app);
void PrintBoilMenu(Application *app);