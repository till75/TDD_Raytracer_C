#include "world.h"

#include <string.h>
//#include "ray.h"
//#include "vecmath.h"
//#include "transforms.h"


void world_Create(World* w) 
{
    w->numberOfObjects = 0;
    w->lightSource = NULL;
}

int world_getNumberOfObjects(World* w)
{
    return w->numberOfObjects;
}

void world_CreateDefault(World* w)
{
    Object sphere1;
    Color default_color = {0.8, 1.0, 0.6};
    Material mat;
    //ray_CreateMaterial(&mat, &default_color, 0.1, 0.7, 0.2, 200.0);
    //ray_CreateSphere(&sphere1, &mat);

    Object sphere2;
    //ray_CreateSphere(&sphere2, &mat);
    Matrix4d sphere_transform;
    transforms_GetScalingMatrix4d(&sphere_transform, 0.5, 0.5, 0.5); 
    //vecmath_CopyMatrix4d(&sphere_transform, &(sphere2.transform));

    world_addObject(&sphere1);
    world_addObject(&sphere2);

}

void world_addObject(Object* obj)
{

}