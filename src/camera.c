#include "camera.h"

static Tuple4d eye;

void camera_Create(Camera* cam, Matrix4d* transform, int w, int h)
{
    cam->width = w;
    cam->height = h;
    cam->focal_length = 2.5; // contained in the z-scaling of the transform
    cam->world_w = 1.0; // should always be set to 1

    
    Tuple4d o = {0,0,0,1};
    vecmath_MultiplyTuple4dByMatrix4d(&o, transform);
    vecmath_CopyTuple4d(&o, &(cam->origin));

///////////////// TODO continue here...
//    vecmath_MultiplyTuple4dByMatrix4d(&f, transform);
//    vecmath_PrintTuple4d(&f);


    // temporary!! to be exchanged for using the transform on all camera vectors
    Tuple4d f = {0,0,1,0};
    vecmath_CopyTuple4d( &f, &(cam->forward_unit));
    Tuple4d back;
    vecmath_CopyTuple4d(&(cam->forward_unit), &back);
    vecmath_ScaleTuple4d(&back, -cam->focal_length);
    vecmath_CopyTuple4d(&(cam->origin), &eye);
    vecmath_AddTuples4d(&eye, &back);

}

void camera_CastRay(Camera* cam, Ray* ray, int x, int y)
{
    Tuple4d r = {1,0,0,0};
    vecmath_CopyTuple4d( &r, &(cam->right_unit));
    Tuple4d u = {0,1,0,0};
    vecmath_CopyTuple4d( &u, &(cam->up_unit));
    
    Tuple4d down, right, p, dir;
    float aspect_ratio = (float)cam->width / (float)cam->height; 
    vecmath_CopyTuple4d(&(cam->right_unit), &right);
    vecmath_ScaleTuple4d(&right, cam->world_w * ((float)(x - cam->width / 2)/(float)cam->width));
    vecmath_CopyTuple4d(&(cam->up_unit), &down);
    vecmath_ScaleTuple4d(&down, -1.0 * cam->world_w / aspect_ratio * ((float)(y - cam->height / 2)/(float)cam->height));
    vecmath_CopyTuple4d(&(cam->origin), &p);
    vecmath_AddTuples4d(&p, &right);
    vecmath_AddTuples4d(&p, &down);

    vecmath_CopyTuple4d(&p, &dir);
    vecmath_SubtractTuples4d(&dir, &eye);
    vecmath_NormalizeTuple4d(&dir);

    vecmath_CopyTuple4d(&eye, &(ray->origin));
    vecmath_CopyTuple4d(&dir, &(ray->direction));
}

void camera_CastRayTransform(Camera* cam, Ray* ray, int x, int y)
{
    
    Tuple4d down, right, back, eye, p, dir;
    float aspect_ratio = (float)cam->width / (float)cam->height; 
    vecmath_CopyTuple4d(&(cam->right_unit), &right);
    vecmath_ScaleTuple4d(&right, cam->world_w * ((float)(x - cam->width / 2)/(float)cam->width));
    vecmath_CopyTuple4d(&(cam->up_unit), &down);
    vecmath_ScaleTuple4d(&down, -1.0 * cam->world_w / aspect_ratio * ((float)(y - cam->height / 2)/(float)cam->height));
    vecmath_CopyTuple4d(&(cam->origin), &p);
    vecmath_AddTuples4d(&p, &right);
    vecmath_AddTuples4d(&p, &down);

    vecmath_CopyTuple4d(&(cam->forward_unit), &back);
    vecmath_ScaleTuple4d(&back, -cam->focal_length);
    vecmath_CopyTuple4d(&(cam->origin), &eye);
    vecmath_AddTuples4d(&eye, &back);

    vecmath_CopyTuple4d(&p, &dir);
    vecmath_SubtractTuples4d(&dir, &eye);
    vecmath_NormalizeTuple4d(&dir);

    vecmath_CopyTuple4d(&eye, &(ray->origin));
    vecmath_CopyTuple4d(&dir, &(ray->direction));
}