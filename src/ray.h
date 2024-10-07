#ifndef RAY_H
#define RAY_H

#define MAX_OBJECTS 10
#include "vecmath.h"

typedef struct 
{
    Tuple4d origin;
    Tuple4d direction;
} Ray;

typedef enum {SPHERE, TRIANGLE, CYLINDER, PLANE, OBJ_NONE} ObjectType;

typedef struct
{
    ObjectType type;
    Tuple4d center;
    float radius;
} Object;

typedef struct
{
    float t;
    Object object;
} Intersection;

typedef struct
{
    Intersection intersections[MAX_OBJECTS];
    int count;
} Intersections;

void ray_CopyObject(Object*, Object*);
void ray_Create(Ray*, Tuple4d*, Tuple4d*);
void ray_GetOriginCopy(Ray*, Tuple4d*);
void ray_GetDirectionCopy(Ray*, Tuple4d*);
void ray_Position(Ray*, Tuple4d*, float);
void ray_CreateSphere(Object*, Tuple4d*, float);
void ray_IntersectSphere(Ray*, Object*, Intersections*);
void ray_Hit(Intersections*, Intersection*);

#endif // RAY_H