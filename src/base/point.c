#include "./point.h"
#include <stdio.h>
#include <stdlib.h>

void ResetPoint(Point *p, char x, char y) {
    p->x = x;
    p->y = y;
}

char GetX(const Point *p) { return p->x; }
char GetY(const Point *p) { return p->y; }

void SetX(Point *p, char x) { p->x = x; }
void SetY(Point *p, char y) { p->y = y; }

void MovePoint(Point *p, char dx, char dy) {
    p->x += dx;
    p->y += dy;
}

void PrintPoint(const Point *p) {
    printf("(%d, %d)\n", p->x, p->y);
}