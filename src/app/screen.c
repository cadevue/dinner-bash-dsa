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
    getchar();
}

void PrintHeader() {
    printf("%s", HEADER);
}