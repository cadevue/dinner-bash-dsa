#pragma once
typedef struct {
    char x;
    char y;
} Point;

void ResetPoint(Point *p, char x, char y);

char GetX(const Point *p);
char GetY(const Point *p);
void SetX(Point *p, char x);
void SetY(Point *p, char y);

void MovePoint(Point *p, char dx, char dy);
void PrintPoint(const Point *p);