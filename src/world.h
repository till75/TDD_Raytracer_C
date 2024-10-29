#ifndef WORLD_H
#define WORLD_H

#include "ray.h"
#include "vecmath.h"
#include "color.h"

/*!
 * \brief World containing objects and one light source
 */
typedef struct
{
    Object objects[MAX_OBJECTS]; /**< Array of spheres and other Objects */
    int numberOfObjects; /**< How many objects are in the world */
    PointLight lightSource;
} World;

/*!
 * @brief Collection of information about ray/object intersection.
 * 
 */
typedef struct
{
    bool isHitFromInside;         /**< Does the ray originate from inside the object? */
    float t;            /**< Distance from ray origin to intersection point */
    Object object;      /**< Intersected object */
    Tuple4d point;      /**< Intersected point in world coords */
    Tuple4d over_point; /**< point very slightly above intersection point for shadow calculations */
    Tuple4d eyeV;       /**< Eye vector at intersection */
    Tuple4d normalV;    /**< Normal vector at intersection */
} Comps;


void world_Create(World*);
int world_getNumberOfObjects(World*);
void world_CreateDefault(World*); //, Object*, Object*, PointLight*);
void world_addObject(World*, Object*);
void world_IntersectRayWithWorld(World*, Ray*, Intersections*);
void world_PrepareComputations(Comps*, Intersection*, Ray*);
void world_ShadeHit(World*, Comps*, Color*);
void world_ColorAt(World*, Ray*, Color*);
bool world_Is_Shadowed(World*, Tuple4d*);
#endif // WORLD_H
