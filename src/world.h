#ifndef WORLD_H
#define WORLD_H

#include <string.h>
#include "ray.h"
#include "transforms.h"
#include "vecmath.h"
#include "color.h"
#include "camera.h"

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
    Tuple4d eyeV;       /**< Eye vector at intersection */
    Tuple4d normalV;    /**< Normal vector at intersection */
} Comps;


void world_Create(World*);
int world_getNumberOfObjects(World*);
void world_CreateDefault(World*, Object*, Object*, PointLight*);
void world_addObject(World*, Object*);
void world_IntersectRayWithWorld(World*, Ray*, Intersections*);
void world_PrepareComputations(Comps*, Intersection*, Ray*);
void world_ShadeHit(World*, Comps*, Color*);
#endif // WORLD_H
