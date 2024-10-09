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
    Matrix4d transform;
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

//void ray_CopyObject(Object*, Object*);
void ray_Create(Ray*, Tuple4d*, Tuple4d*);
void ray_GetOriginCopy(Ray*, Tuple4d*);
//void ray_GetDirectionCopy(Ray*, Tuple4d*);
void ray_Position(Ray*, Tuple4d*, float);
void ray_CreateSphere(Object*, Tuple4d*, float);
void ray_IntersectSphere(Ray*, Object*, Intersections*);
void ray_Hit(Intersections*, Intersection*);
void ray_BubbleSortIntegers(int[], int);
void ray_BubbleSortIntersections(Intersections*);
void ray_Transform(Ray*, Ray*, Matrix4d*);
void ray_ObjectSetTransform(Object*, Matrix4d*);
void ray_NormalAt(Object*, Tuple4d*, Tuple4d*);
void ray_Reflect(Tuple4d*, Tuple4d*, Tuple4d*);

#endif // RAY_H