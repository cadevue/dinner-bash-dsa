#pragma once
#include "app.h"

void ClearScreen();
void PrintSplashScreen();
void PrintHeader();
void PrintHelp();
void PrintLegend();
void PrintMap(const Application *app);
void PrintProgressBar(int progress, int total);