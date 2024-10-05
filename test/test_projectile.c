#ifdef TEST

#include "unity.h"
#include "vecmath.h"
#include "projectile.h"
#include "canvas.h"
#include "color.h"
#include "transforms.h"

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

void test_projectile_CircleTickToFile(void)
{

    Tuple4d pos = {0,0,0,1};
    Matrix4d rot_z = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d tr_1 = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetTranslationMatrix4d(&tr_1, 0, 40, 0);
    Matrix4d tr_2 = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};

    Canvas canvas;
    canvas_Create(&canvas, 100, 100);
    Color red;
    color_Create(&red, 1, 0, 0);

    for (int i = 0; i < 12; i++)
    {
        pos[0] = 0; pos[1] = 0; // reset pos
        transforms_GetRotationZMatrix4d(&rot_z, M_PI / 6 * (float)i); // new rot matrix for each tick
        transforms_GetTranslationMatrix4d(&tr_2, 50, 50, 0); // reset tr_2

        vecmath_MultiplyMatrix4d(&tr_2, &rot_z);
        vecmath_MultiplyMatrix4d(&tr_2, &tr_1);
        vecmath_MultiplyTuple4dByMatrix4d(&pos, &tr_2);

        int x = (int)pos[0];
        int y = (int)pos[1];
        canvas_DrawPixel(&canvas, &red, x, canvas.height - y);

    }

    canvas_PixelsToPPMFile(&canvas, "circle.ppm");
    canvas_Destroy(&canvas);
}

#endif // TEST
