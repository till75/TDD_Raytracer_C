#ifndef CAMERA_H
#define CAMERA_H

#include "vecmath.h"
#include "canvas.h"
#include "ray.h"

typedef struct 
{
    Tuple4d origin, forward_unit, up_unit, right_unit;
    float focal_length, world_w;
    int width, height, current_x, current_y;
} Camera;

void camera_CastRay(Camera*, Ray*, int, int);
#endif // CAMERA_H
