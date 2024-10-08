#include "camera.h"

void camera_CastRay(Camera* cam, Ray* ray, int x, int y)
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