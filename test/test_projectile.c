#ifdef TEST

#include "unity.h"
#include "vecmath.h"
#include "projectile.h"
#include "canvas.h"
#include "color.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_projectile_Create(void)
{
    Projectile projectile;
    Tuple4d pos = {0,1,0,1};
    Tuple4d vel = {1,1,0,0};
    vecmath_NormalizeTuple4d(&vel);
    projectile_Create(&projectile, &pos, &vel);
    
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(projectile.position, &pos));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(projectile.velocity, &vel));
    
    Environment environment;
    Tuple4d gravity = {0, -0.1, 0, 9};
    Tuple4d wind = {-0.01, 0, 0, 0};
    projectile_CreateEnv(&environment, &gravity, &wind);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(environment.gravity, &gravity));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(environment.wind, &wind));
}

void test_projectile_PrintTick(void)
{
    Projectile projectile;
    Tuple4d pos = {0,1,0,1};
    Tuple4d vel = {1,1,0,0};
    vecmath_NormalizeTuple4d(&vel);
    projectile_Create(&projectile, &pos, &vel);
    
    Environment environment;
    Tuple4d gravity = {0, -0.1, 0, 9};
    Tuple4d wind = {-0.01, 0, 0, 0};
    projectile_CreateEnv(&environment, &gravity, &wind);

    int i = 0;
    do
    {
        // printf("\nPosition (%d): ", i);
        // vecmath_PrintTuple(projectile.position);
        // printf("  Velocity (%d): ", i);
        // vecmath_PrintTuple(projectile.velocity);
        i++;

        projectile_tick(&projectile, &environment);
        
    } while ((*projectile.position)[1] > 0.0);

    TEST_ASSERT_TRUE(i == 17);
}

void test_projectile_CanvasTickToFile(void)
{
    Projectile projectile;
    Tuple4d pos = {0,1,0};
    Tuple4d vel = {1, 1.8, 0};
    vecmath_NormalizeTuple4d(&vel);
    vecmath_ScaleTuple4d(&vel, 11.25);
    projectile_Create(&projectile, &pos, &vel);
    
    Environment environment;
    Tuple4d gravity = {0, -0.1, 0, 9};
    Tuple4d wind = {-0.01, 0, 0, 0};
    projectile_CreateEnv(&environment, &gravity, &wind);

    Canvas canvas;
    canvas_Create(&canvas, 900, 550);
    Color red;
    color_Create(&red, 1, 0, 0);

    int i=0;
    do
    {
        int x = (int)(*projectile.position)[0];
        int y = (int)(*projectile.position)[1];

        //int y = (int)(((float)canvas.height) - projectile.position->y);
        canvas_DrawPixel(&canvas, &red, x, canvas.height - y);

        // printf("\nP (%d): ", i);
        // vecmath_PrintTuple(projectile.position);
        // printf("  V (%d): ", i++);
        // vecmath_PrintTuple(projectile.velocity);

        // printf("(%d) x=%d / y=%d\n", i++, x, y);
        projectile_tick(&projectile, &environment);
    } while ((*projectile.position)[1] > 0.0);

    canvas_PixelsToPPMFile(&canvas, "image.ppm");
    canvas_Destroy(&canvas);
}

#endif // TEST
