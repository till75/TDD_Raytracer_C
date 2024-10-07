#ifndef RAY_H
#define RAY_H

#include "vecmath.h"

typedef struct 
{
    Tuple4d origin;
    Tuple4d direction;
} Ray;

void ray_Create(Ray*, Tuple4d*, Tuple4d*);

#endif // RAY_H