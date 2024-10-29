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

void world_CreateDefault(World* w)
{
    w->numberOfObjects = 0;
    Object sphere1;
    Color color1 = {0.8, 1.0, 0.6};
    Material mat;
    ray_CreateMaterial(&mat, &color1, 0.1, 0.7, 0.2, 200.0);
    ray_CreateSphere(&sphere1, &mat);

    Object sphere2;
    Color color2 = {1, 1, 1};
    Material mat2;
    ray_CreateMaterial(&mat2, &color2, 0.1, 0.9, 0.9, 200.0); // default material!
    ray_CreateSphere(&sphere2, &mat2);
    Matrix4d sphere_transform;
    transforms_GetScalingMatrix4d(&sphere_transform, 0.5, 0.5, 0.5); 
    vecmath_CopyMatrix4d(&sphere_transform, &(sphere2.transform));

    PointLight light = {{-10,10,-10,1},{1,1,1}};

    world_addObject(w, &sphere1);
    world_addObject(w, &sphere2);
    w->lightSource = light;
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
    vecmath_CopyTuple4d(&(comps->normalV), &dir);
    vecmath_ScaleTuple4d(&dir, EPSILON*100);
    vecmath_CopyTuple4d(&(comps->point), &(comps->over_point));
    vecmath_AddTuples4d(&(comps->over_point), &dir);
}

void world_ShadeHit(World* world, Comps* comps, Color* resultColor)
{
    bool is_shadowed = world_Is_Shadowed(world, &(comps->over_point));
    ray_Lighting(resultColor, &((comps->object).material), &(world->lightSource), &(comps->point), 
                    &(comps->eyeV), &(comps->normalV), is_shadowed);
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

bool world_Is_Shadowed(World* world, Tuple4d* p)
{
    Tuple4d v;
    vecmath_CopyTuple4d(&((world->lightSource).pos), &v);
    vecmath_SubtractTuples4d(&v, p);
    float distance = vecmath_MagnitudeTuple4d(&v);
    Ray r;
    vecmath_CopyTuple4d(&v, &(r.direction));
    vecmath_NormalizeTuple4d(&(r.direction));
    vecmath_CopyTuple4d(p, &(r.origin));

    Intersections ints;
    ints.count = 0;
    world_IntersectRayWithWorld(world, &r, &ints);
    Intersection hit;
    ray_Hit(&ints, &hit);

    if ((hit.object.type != OBJ_NONE) && (hit.t < distance))
        return true;
    else
        return false;
}
