#include "camera.h"
#include "transforms.h"
#include "vecmath.h"
#include "world.h"
#include <math.h>

//static Tuple4d eye;

// void camera_Create(Camera* cam, Matrix4d* transform, int w, int h)
// {
//     cam->width = w;
//     cam->height = h;
//     cam->focal_length = 2.5; // contained in the z-scaling of the transform
//     cam->world_w = 1.0; // should always be set to 1

    
//     Tuple4d o = {0,0,0,1};
//     vecmath_MultiplyTuple4dByMatrix4d(&o, transform);
//     vecmath_CopyTuple4d(&o, &(cam->origin));

// ///////////////// TODO continue here...
// //    vecmath_MultiplyTuple4dByMatrix4d(&f, transform);
// //    vecmath_PrintTuple4d(&f);


//     // temporary!! to be exchanged for using the transform on all camera vectors
//     Tuple4d f = {0,0,1,0};
//     vecmath_CopyTuple4d( &f, &(cam->forward_unit));
//     Tuple4d back;
//     vecmath_CopyTuple4d(&(cam->forward_unit), &back);
//     vecmath_ScaleTuple4d(&back, -cam->focal_length);
//     vecmath_CopyTuple4d(&(cam->origin), &eye);
//     vecmath_AddTuples4d(&eye, &back);

// }

void camera_Create2(Camera2* camera, int hsize, int vsize, float fov)
{
    camera->hsize = hsize;
    camera->vsize = vsize;
    camera->fov = fov;
    Matrix4d trans = UNITY_TRANSFORM;
    vecmath_CopyMatrix4d(&trans, &(camera->transform));
}

void camera_InitPixelSize(Camera2* camera)
{
    float half_view = tan(camera->fov/2.0);
    float aspect_ratio = (float)camera->hsize / (float)camera->vsize;
    if (aspect_ratio >= 1.0)
    {
        camera->half_width = half_view;
        camera->half_height = half_view / aspect_ratio;
    }
    else
    {
        camera->half_width = half_view * aspect_ratio;
        camera->half_height = half_view;
    }
    camera->pixel_size = (camera->half_width * 2.0) / camera->hsize;
}

void camera_RayForPixel(Camera2* camera, Ray* ray, int x, int y)
{
    float x_offset = ((float)x + 0.5) * camera->pixel_size;
    float y_offset = ((float)y + 0.5) * camera->pixel_size;

    float world_x = camera->half_width - x_offset;
    float world_y = camera->half_height - y_offset;
    
    Matrix4d inv;
    vecmath_FastInverseMatrix4d(&(camera->transform), &inv);
    Tuple4d pixel = {world_x, world_y, -1, 1};
    vecmath_MultiplyTuple4dByMatrix4d(&pixel, &inv);
    Tuple4d origin = {0,0,0,1};
    vecmath_MultiplyTuple4dByMatrix4d(&origin, &inv);
    vecmath_CopyTuple4d(&origin, &(ray->origin));
    vecmath_SubtractTuples4d(&pixel, &origin);
    vecmath_NormalizeTuple4d(&pixel);
    vecmath_CopyTuple4d(&pixel, &(ray->direction));
}

void camera_SetViewTransform(Camera2* cam, Tuple4d* from, Tuple4d* to, Tuple4d* up)
{
    Matrix4d* res = &(cam->transform);
    Tuple4d forward;
    vecmath_CopyTuple4d(to, &forward);
    vecmath_SubtractTuples4d(&forward, from);
    vecmath_NormalizeTuple4d(&forward);
    Tuple4d upn; 
    vecmath_CopyTuple4d(up, &upn);
    vecmath_NormalizeTuple4d(&upn);
    Tuple4d left;
    vecmath_CrossProductTuple4d(&left, &forward, &upn);
    Tuple4d true_up;
    vecmath_CrossProductTuple4d(&true_up, &left, &forward);
    // Orientation matrix
    (*res)[0][0] =     left[0]; (*res)[0][1] =     left[1]; (*res)[0][2] =     left[2]; (*res)[0][3] = 0;
    (*res)[1][0] =  true_up[0]; (*res)[1][1] =  true_up[1]; (*res)[1][2] =  true_up[2]; (*res)[1][3] = 0;
    (*res)[2][0] = -forward[0]; (*res)[2][1] = -forward[1]; (*res)[2][2] = -forward[2]; (*res)[2][3] = 0;
    (*res)[3][0] =           0; (*res)[3][1] =           0; (*res)[3][2] =           0; (*res)[3][3] = 1;

    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, -(*from)[0], -(*from)[1], -(*from)[2]);
    vecmath_MultiplyMatrix4d(res, &transl);
}

void camera_RenderImage(Camera2* cam, World* world, Canvas* canvas)
{
    Ray ray;
    Color color;
    for (int y = 0; y < canvas->height; y++)
    {
        for (int x = 0; x < canvas->width; x++)
        {
            camera_RayForPixel(cam, &ray, x, y);
            world_ColorAt(world, &ray, &color);
            canvas_DrawPixel(canvas, &color, x, y);
        }
    }
}

// void camera_CastRay(Camera* cam, Ray* ray, int x, int y)
// {
//     Tuple4d r = {1,0,0,0};
//     vecmath_CopyTuple4d( &r, &(cam->right_unit));
//     Tuple4d u = {0,1,0,0};
//     vecmath_CopyTuple4d( &u, &(cam->up_unit));
    
//     Tuple4d down, right, p, dir;
//     float aspect_ratio = (float)cam->width / (float)cam->height; 
//     vecmath_CopyTuple4d(&(cam->right_unit), &right);
//     vecmath_ScaleTuple4d(&right, cam->world_w * ((float)(x - cam->width / 2)/(float)cam->width));
//     vecmath_CopyTuple4d(&(cam->up_unit), &down);
//     vecmath_ScaleTuple4d(&down, -1.0 * cam->world_w / aspect_ratio * ((float)(y - cam->height / 2)/(float)cam->height));
//     vecmath_CopyTuple4d(&(cam->origin), &p);
//     vecmath_AddTuples4d(&p, &right);
//     vecmath_AddTuples4d(&p, &down);

//     vecmath_CopyTuple4d(&p, &dir);
//     vecmath_SubtractTuples4d(&dir, &eye);
//     vecmath_NormalizeTuple4d(&dir);

//     vecmath_CopyTuple4d(&eye, &(ray->origin));
//     vecmath_CopyTuple4d(&dir, &(ray->direction));
// }

// void camera_CastRayTransform(Camera* cam, Ray* ray, int x, int y)
// {
    
//     Tuple4d down, right, back, eye, p, dir;
//     float aspect_ratio = (float)cam->width / (float)cam->height; 
//     vecmath_CopyTuple4d(&(cam->right_unit), &right);
//     vecmath_ScaleTuple4d(&right, cam->world_w * ((float)(x - cam->width / 2)/(float)cam->width));
//     vecmath_CopyTuple4d(&(cam->up_unit), &down);
//     vecmath_ScaleTuple4d(&down, -1.0 * cam->world_w / aspect_ratio * ((float)(y - cam->height / 2)/(float)cam->height));
//     vecmath_CopyTuple4d(&(cam->origin), &p);
//     vecmath_AddTuples4d(&p, &right);
//     vecmath_AddTuples4d(&p, &down);

//     vecmath_CopyTuple4d(&(cam->forward_unit), &back);
//     vecmath_ScaleTuple4d(&back, -cam->focal_length);
//     vecmath_CopyTuple4d(&(cam->origin), &eye);
//     vecmath_AddTuples4d(&eye, &back);

//     vecmath_CopyTuple4d(&p, &dir);
//     vecmath_SubtractTuples4d(&dir, &eye);
//     vecmath_NormalizeTuple4d(&dir);

//     vecmath_CopyTuple4d(&eye, &(ray->origin));
//     vecmath_CopyTuple4d(&dir, &(ray->direction));
// }