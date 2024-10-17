/*!
 * @file ray.h
 * @author Till Seyfarth
 * @brief 
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#ifndef RAY_H
#define RAY_H

#define MAX_OBJECTS 10
#include "vecmath.h"
#include "color.h"

typedef struct 
{
    Tuple4d origin;
    Tuple4d direction;
} Ray;

typedef struct 
{
    Color color;
    float ambient;
    float diffuse;
    float specular;
    float shininess;
} Material;

typedef enum {SPHERE, TRIANGLE, CYLINDER, PLANE, OBJ_NONE} ObjectType;

typedef struct
{
    ObjectType type;
    Matrix4d transform;
    Material material;
} Object;

/*!
 * @brief Intersection with object at distance t.
 * 
 */
typedef struct
{
    float t;        /**< Distance to intersection */
    Object object;  /**< Intersected object */
} Intersection;

typedef struct
{
    Intersection intersections[MAX_OBJECTS];
    int count;
} Intersections;

typedef struct
{
    Tuple4d pos;
    Color intensity;
} PointLight;

//void ray_CopyObject(Object*, Object*);
void ray_Create(Ray*, Tuple4d*, Tuple4d*);
void ray_GetOriginCopy(Ray*, Tuple4d*);
//void ray_GetDirectionCopy(Ray*, Tuple4d*);
void ray_Position(Ray*, Tuple4d*, float);
void ray_CreateSphere(Object*, Material*);
void ray_IntersectSphere(Ray*, Object*, Intersections*);
void ray_Hit(Intersections*, Intersection*);
void ray_BubbleSortIntegers(int[], int);
void ray_BubbleSortIntersections(Intersections*);
void ray_Transform(Ray*, Ray*, Matrix4d*);
void ray_ObjectSetTransform(Object*, Matrix4d*);
void ray_NormalAt(Object*, Tuple4d*, Tuple4d*);
void ray_Reflect(Tuple4d*, Tuple4d*, Tuple4d*);
void ray_CreatePointLight(PointLight*, Tuple4d*, Color*);
void ray_CreateDefaultMaterial(Material*);
void ray_Lighting(Color*, Material*, PointLight*, Tuple4d*, Tuple4d*, Tuple4d*);
void ray_CreateMaterial(Material*, Color*, float, float, float, float);

#endif // RAY_H