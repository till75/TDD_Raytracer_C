#include "ray.h"
#include <stdio.h>

void ray_Create(Ray* r, Tuple4d* o, Tuple4d* d)
{
    r->origin[0] = (*o)[0]; 
    r->origin[1] = (*o)[1]; 
    r->origin[2] = (*o)[2]; 
    r->origin[3] = 1.0;

    r->direction[0] = (*d)[0]; 
    r->direction[1] = (*d)[1]; 
    r->direction[2] = (*d)[2]; 
    r->direction[3] = 0.0;
}