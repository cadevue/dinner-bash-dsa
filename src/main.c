#include <stdio.h>
#include "./info/point.h"

int main ()
{
    printf("Application Started!\n");

    Point p = {1, 2};
    PrintPoint(&p);

    return 0;
}
