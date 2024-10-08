#ifdef TEST

#include "unity.h"

#include "camera.h"
#include "color.h"
#include "canvas.h"
#include "ray.h"
#include "vecmath.h"
#include "transforms.h"


void setUp(void)
{
}

void tearDown(void)
{
}

void test_camera_Create(void)
{
    int w = 200;
    int h = 160;
    Color red = {1,0,0};
    Color black = {0,0,0};
    Canvas canvas;
    canvas_Create(&canvas, w, h);

    float cam_pos_x = 0, cam_pos_y = 0, cam_pos_z = -5;
    Matrix4d cam_translate;
    transforms_GetTranslationMatrix4d(&cam_translate, cam_pos_x, cam_pos_y, cam_pos_z);
    
    float cam_world_width = 1.0;
    float cam_world_height = cam_world_width * (float)w / (float)h;
    float cam_focal_length = 2.5; 
    Matrix4d cam_scale;
    transforms_GetScalingMatrix4d(&cam_scale, cam_world_width, cam_world_height, cam_focal_length);
    
    float cam_rot_x = 0;
    Matrix4d cam_rotation_x;
    transforms_GetRotationXMatrix4d(&cam_rotation_x, cam_rot_x);
    
    float cam_rot_y = 0;
    Matrix4d cam_rotation_y;
    transforms_GetRotationYMatrix4d(&cam_rotation_y, cam_rot_y);
    
    float cam_rot_z = 0; // 10.0 * M_PI / 180.0;
    Matrix4d cam_rotation_z;
    transforms_GetRotationZMatrix4d(&cam_rotation_z, cam_rot_z);

    Matrix4d cam_transform = UNITY_TRANSFORM;
    vecmath_MultiplyMatrix4d(&cam_transform, &cam_translate);
    vecmath_MultiplyMatrix4d(&cam_transform, &cam_scale);
    vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_x);
    vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_y);
    vecmath_MultiplyMatrix4d(&cam_transform, &cam_rotation_z);

    Camera cam; // = { cam_transform, {0,0,-5,1}, {0,0,1,0}, {0,1,0,0}, {1,0,0,0}, 2.5, 1.0, w, h, 0, 0};
    camera_Create(&cam, &cam_transform, w, h);

    Ray ray = {{0,0,0,0},{0,0,0,0}};
    Matrix4d sphere_transform;
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    transforms_GetScalingMatrix4d(&sphere_transform, 1.2,0.6,1); 
    vecmath_CopyMatrix4d(&sphere_transform, &(sphere.transform));
    Object nothing = {OBJ_NONE, UNITY_TRANSFORM};
    Intersection clostestHit = {0, nothing};
    Intersections ints = {{clostestHit}, 1};

    int x = 0;
    int y = 0;
    do
    {
        camera_CastRay(&cam, &ray, x, y);
        ray_IntersectSphere(&ray, &sphere, &ints);
        ray_Hit(&ints, &clostestHit);
        if (clostestHit.object.type != OBJ_NONE)
        {
            canvas_DrawPixel(&canvas, &red, x, y);
            //printf("r-");
            clostestHit.object = nothing;
            ints.intersections[0] = clostestHit;

        }
        else
        {
            canvas_DrawPixel(&canvas, &black, x, y);
            //printf("B-");
        }


        x++;
        if (x > cam.width-1)
        {
            x = 0;
            y ++;
            //printf("\n");
        }
    } while (y < cam.height);
    canvas_PixelsToPPMFile(&canvas, "sphere.ppm");
    canvas_Destroy(&canvas);    
}

#endif // TEST
