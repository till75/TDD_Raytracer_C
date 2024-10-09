#include "ray.h"
#include "vecmath.h"
#include <stdio.h>
#include <math.h>
#include <float.h>

void ray_Create(Ray* r, Tuple4d* o, Tuple4d* d)
{
    vecmath_CopyTuple4d(o, &(r->origin));
    vecmath_CopyTuple4d(d, &(r->direction));
}

void ray_GetOriginCopy(Ray* r, Tuple4d* p)
{
    vecmath_CopyTuple4d(&(r->origin), p);
}

void ray_GetDirectionCopy(Ray* r, Tuple4d* d)
{
    vecmath_CopyTuple4d(&(r->direction), d);
}

void ray_Position(Ray* r, Tuple4d* res, float t)
{
    Tuple4d tmp;
    ray_GetDirectionCopy(r, &tmp);
    vecmath_NormalizeTuple4d(&tmp);
    vecmath_ScaleTuple4d(&tmp, t);
    ray_GetOriginCopy(r, res);
    vecmath_AddTuples4d(res, &tmp); 
}


// TODO: Consider passing sorted intersections in and inserting hits to keep the array sorted!
void ray_IntersectSphere(Ray* ray, Object* obj, Intersections* i)
{
    Matrix4d inverse_transform;
    vecmath_FastInverseMatrix4d(&(obj->transform), &inverse_transform);
    Ray r;
    ray_Transform(ray, &r, &inverse_transform);
    
    Tuple4d sphere_to_ray = {r.origin[0], r.origin[1], r.origin[2], 0};
    float a = vecmath_DotProductTuple4d(&(r.direction), &(r.direction));
    float b = 2.0 * vecmath_DotProductTuple4d(&(r.direction), &sphere_to_ray);
    float c = vecmath_DotProductTuple4d(&sphere_to_ray, &sphere_to_ray) - 1.0;

    float discriminant = b*b - 4.0 * a * c;

    if (discriminant < 0.0)
    {
        i->count=0;
    }        
    else
    {
        float sqrt_disc = sqrt(discriminant);
        if (sqrt_disc < 0)
        {
            i->intersections[0].t = (-b + sqrt_disc) / (2.0 * a);
            i->intersections[1].t = (-b - sqrt_disc) / (2.0 * a);
        }
        else
        {
            i->intersections[0].t = (-b - sqrt_disc) / (2.0 * a);
            i->intersections[1].t = (-b + sqrt_disc) / (2.0 * a);
        }
        i->count=2;
        i->intersections[0].object = *obj;
        i->intersections[1].object = *obj;
    }
}

void ray_Hit(Intersections* ints, Intersection* res)
{
    int i = 0;
    int i_closest = -1;
    float t_closest = FLT_MAX;
    do 
    {
        if (ints->intersections[i].t > 0 && ints->intersections[i].t < t_closest)
        {
            i_closest = i;
            t_closest = ints->intersections[i].t;
        }
        i++;
    } while (i < ints->count);
    if (i_closest >= 0)
    {
        res->object = ints->intersections[i_closest].object;
        res->t = ints->intersections[i_closest].t;
    }
    else
    {
        res->object.type = OBJ_NONE;
    }
}

void ray_BubbleSortIntegers(int a[], int array_size)
{
    int i, j, temp;
    for (i = 0; i < (array_size - 1); ++i) 
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
            if (a[j] > a[j+1]) 
            {
                temp = a[j+1];
                a[j+1] = a[j];
                a[j] = temp;
            }
        }
    }
}

void ray_BubbleSortIntersections(Intersections* ints)
{
    int i, j;
    Intersection temp;
    int array_size = ints->count;
    for (i = 0; i < (array_size - 1); ++i) 
    {
        for (j = 0; j < array_size - 1 - i; ++j )
        {
            if (ints->intersections[j].t > ints->intersections[j+1].t) 
            {
                temp = ints->intersections[j+1];
                ints->intersections[j+1] = ints->intersections[j];
                ints->intersections[j] = temp;
            }
        }
    }
}

void ray_Transform(Ray* r, Ray* r_res, Matrix4d* transform)
{
    *r_res = *r;
    //Matrix4d m;
    //vecmath_FastInverseMatrix4d(transform, &m);
    vecmath_MultiplyTuple4dByMatrix4d(&(r_res->origin), transform);
    vecmath_MultiplyTuple4dByMatrix4d(&(r_res->direction), transform);
}

void ray_ObjectSetTransform(Object* o, Matrix4d* m)
{
    vecmath_CopyMatrix4d(m, &(o->transform));
}

void ray_NormalAt(Object* obj, Tuple4d* world_p, Tuple4d* n)
{
    Tuple4d object_p;
    vecmath_CopyTuple4d(world_p, &object_p);
    Matrix4d inverse_transform;
    vecmath_FastInverseMatrix4d(&(obj->transform), &inverse_transform);
    vecmath_MultiplyTuple4dByMatrix4d(&object_p, &inverse_transform);

    Tuple4d origin = {0,0,0,1};
    vecmath_SubtractTuples4d(&object_p, &origin);
    vecmath_CopyTuple4d(&object_p, n);

    vecmath_TranssposeMatrix4d(&inverse_transform);
    vecmath_MultiplyTuple4dByMatrix4d(n, &inverse_transform);
    (*n)[3] = 0.0;
    vecmath_NormalizeTuple4d(n);
}

void ray_Reflect(Tuple4d* vector, Tuple4d* normal, Tuple4d* reflected)
{
    Tuple4d tmp_n;
    float dot = vecmath_DotProductTuple4d(vector, normal);
    vecmath_CopyTuple4d(normal, &tmp_n);
    vecmath_ScaleTuple4d(&tmp_n, 2.0 * dot);
    Tuple4d tmp_v;
    vecmath_CopyTuple4d(vector, &tmp_v);
    vecmath_SubtractTuples4d(&tmp_v, &tmp_n);
    vecmath_CopyTuple4d(&tmp_v, normal);
}