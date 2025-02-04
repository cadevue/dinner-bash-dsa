#include "./point.h"
#include <stdio.h>
#include <stdlib.h>

void ResetPoint(Point *p, int x, int y) {
    p->x = x;
    p->y = y;
}

int GetX(const Point *p) { return p->x; }
int GetY(const Point *p) { return p->y; }

void SetX(Point *p, int x) { p->x = x; }
void SetY(Point *p, int y) { p->y = y; }

void MovePoint(Point *p, int dx, int dy) {
    p->x += dx;
    p->y += dy;
}

void PrintPoint(const Point *p) {
    printf("(%d, %d)\n", p->x, p->y);
}