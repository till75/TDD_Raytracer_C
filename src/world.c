#include <string.h>
#include "world.h"
#include "ray.h"
#include "vecmath.h"
#include "transforms.h"


void world_Create(World* w) 
{
    w->numberOfObjects = 0;
    //*(w->lightSource) = (PointLight)NULL;
}

int world_getNumberOfObjects(World* w)
{
    return w->numberOfObjects;
}

void world_CreateDefault(World* w, Object* o1, Object* o2, PointLight* light)
{
    world_addObject(w, o1);
    world_addObject(w, o2);
    w->lightSource = *(light);
}

void world_addObject(World* w, Object* obj)
{
    w->objects[w->numberOfObjects] = *(obj);
    w->numberOfObjects += 1;
}

void world_IntersectRayWithWorld(World* world, Ray* ray, Intersections* ints)
{
    Object obj;
    for (int obj_no = 0; obj_no < world->numberOfObjects; obj_no++)
    {
        obj = (world->objects)[obj_no];
        switch (obj.type)
        {
            case SPHERE:
            ray_IntersectSphere(ray, &obj, ints);
            break;
        }
    }
}

void world_PrepareComputations(Comps* comps, Intersection* inter, Ray* ray)
{
    comps->t = inter->t;
    comps->object = inter->object;

    Tuple4d pt = {0,0,0,0};
    ray_Position(ray, &pt, comps->t);
    vecmath_CopyTuple4d(&pt, &(comps->point));

    Tuple4d dir = {0,0,0,0};
    vecmath_CopyTuple4d(&(ray->direction), &dir);
    vecmath_ScaleTuple4d(&dir, -1.0);
    vecmath_CopyTuple4d(&dir, &(comps->eyeV));

    ray_NormalAt(&(comps->object), &(comps->point), &dir);
    vecmath_CopyTuple4d(&dir, &(comps->normalV));

    if (vecmath_DotProductTuple4d(&(comps->eyeV), &(comps->normalV)) < 0.0) 
    {
        comps->isHitFromInside = true;
        vecmath_ScaleTuple4d(&(comps->normalV), -1.0);
    }
    else
    {
        comps->isHitFromInside = false;
    }
}

void world_ShadeHit(World* world, Comps* comps, Color* resultColor)
{
    ray_Lighting(resultColor, &((comps->object).material), &(world->lightSource), &(comps->point), &(comps->eyeV), &(comps->normalV));
}

void world_ColorAt(World* world, Ray* ray, Color* resultColor)
{
    Intersections ints;
    ints.count = 0;
    world_IntersectRayWithWorld(world, ray, &ints);
    Intersection closest;
    ray_Hit(&ints, &closest);
    Comps comps;
    if (closest.object.type != OBJ_NONE)
    {
        world_PrepareComputations(&comps, &closest, ray);
        world_ShadeHit(world, &comps, resultColor);
    }
    else
    {
        resultColor->red=0.0;
        resultColor->green=0.0;
        resultColor->blue=0.0;
    }
}