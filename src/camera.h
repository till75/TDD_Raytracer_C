#ifndef CAMERA_H
#define CAMERA_H

#include "vecmath.h"
#include "world.h"
#include "canvas.h"

// typedef struct 
// {
//     Matrix4d transform;
//     Tuple4d origin, forward_unit, up_unit, right_unit;
//     float focal_length, world_w;
//     int width, height, current_x, current_y;
// } Camera;

typedef struct
{
    int hsize;          /**< horizontal size in pixels */
    int vsize;          /**< vertical size in pixels */
    float fov;          /**< field of view in radians */
    float half_width;   /**< half width of the screen in world coordinates */
    float half_height;  /**< half height of the screen in world coordinates */
    float pixel_size;   /**< width and height of a pixel in world coordinates */
    Matrix4d transform; /**< view transform */
} Camera2;

//void camera_Create(Camera*, Matrix4d*, int, int);
//void camera_CastRay(Camera*, Ray*, int, int);
//void camera_CastRayTransform(Camera*, Ray*, int, int);

void camera_Create2(Camera2* camera, int hsize, int vsize, float fov);
void camera_InitPixelSize(Camera2* camera);
void camera_RayForPixel(Camera2* camera, Ray* ray, int x, int y);
void camera_SetViewTransform(Camera2* cam, Tuple4d* from, Tuple4d* to, Tuple4d* up);
void camera_RenderImage(Camera2* cam, World* world, Canvas* canvas);

#endif // CAMERA_H
