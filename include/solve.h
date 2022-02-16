#pragma once
#include "city.h"

typedef struct ans
{
    double dist;
    int *route;
} Answer;

double solve(const City *city, int n, int *route);

void search(const City *city, int n, int *route, double *min_sum);
