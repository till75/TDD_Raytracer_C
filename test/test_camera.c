#ifdef TEST

#include "unity.h"

#include "camera.h"
#include "color.h"
#include "canvas.h"
#include "ray.h"
#include "vecmath.h"


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
    // Color pixels[h * w]; 
    Color red = {1,0,0};
    Color black = {0,0,0};
    Canvas canvas; // = {pixels, w, h};
    canvas_Create(&canvas, w, h);
    Camera cam = {{0,0,-5,1}, {0,0,1,0}, {0,1,0,0}, {1,0,0,0}, 2.5, 1.0, w, h, 0, 0};
    Ray ray = {{0,0,0,0},{0,0,0,0}};
    Object sphere = {SPHERE, UNITY_TRANSFORM};
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
            printf("\n");
        }
    } while (y < cam.height);
    canvas_PixelsToPPMFile(&canvas, "sphere.ppm");
    canvas_Destroy(&canvas);    
}

#endif // TEST
