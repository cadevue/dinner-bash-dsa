#pragma once
typedef struct {
    int x;
    int y;
} Point;

int GetX(const Point *p);
int GetY(const Point *p);
void SetX(Point *p, int x);
void SetY(Point *p, int y);

void MovePoint(Point *p, int dx, int dy);
void PrintPoint(const Point *p);