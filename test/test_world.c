/*!
 * @file test_world.c
 * @author Till Seyfarth
 * @brief Tests for world functions.
 * @date 2024-10-17
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#ifdef TEST

#include "unity.h"
#include <string.h>
#include "world.h"
#include "ray.h"
#include "vecmath.h"
#include "transforms.h"
#include "color.h"
// #include "camera.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_world_EmptyOnCreation(void)
{
    World w;
    world_Create(&w);

    TEST_ASSERT_TRUE(world_getNumberOfObjects(&w) == 0);
}

void test_world_CreateDefault(void)
{
    World w;
    world_CreateDefault(&w);

    TEST_ASSERT_EQUAL(2, w.numberOfObjects);
}

void test_world_DefaultWorldIntersectsFourTimesWithZAxisRay(void)
{
    World world;
    world_CreateDefault(&world);
    Ray ray = {{0,0,-5,1},{0,0,1,0}};
    Intersections ints;
    ints.count = 0;
    world_IntersectRayWithWorld(&world, &ray, &ints);

    TEST_ASSERT_EQUAL(4, ints.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.0, ints.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.5, ints.intersections[1].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.5, ints.intersections[2].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 6.0, ints.intersections[3].t);
}

void test_world_PrecomputeIntersectionState(void)
{
    Ray ray = {{0,0,-5,1},{0,0,1,0}};
    Object sphere1;
    Color default_color = {0.8, 1.0, 0.6};
    Material mat;
    ray_CreateMaterial(&mat, &default_color, 0.1, 0.7, 0.2, 200.0);
    ray_CreateSphere(&sphere1, &mat);
    Intersection inter = {4.0, sphere1};
    Comps comps;
    world_PrepareComputations(&comps, &inter, &ray);

    Tuple4d pt = {0,0,-1,1};
    Tuple4d vec = {0,0,-1,0};

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, inter.t, comps.t);
    TEST_ASSERT_EQUAL(SPHERE, comps.object.type);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&pt, &(comps.point)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&vec, &(comps.eyeV)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&vec, &(comps.normalV)));
}

void test_world_PrecomputeIntersectionState_HitObjectFromOutside(void)
{
    Ray ray = {{0,0,-5,1},{0,0,1,0}};
    Object sphere1;
    Color default_color = {0.8, 1.0, 0.6};
    Material mat;
    ray_CreateMaterial(&mat, &default_color, 0.1, 0.7, 0.2, 200.0);
    ray_CreateSphere(&sphere1, &mat);
    Intersection inter = {4.0, sphere1};
    Comps comps;
    world_PrepareComputations(&comps, &inter, &ray);

    Tuple4d pt = {0,0,-1,1};
    Tuple4d vec = {0,0,-1,0};

    TEST_ASSERT_FALSE(comps.isHitFromInside);
}

void test_world_PrecomputeIntersectionState_HitFromWithinObject(void)
{
    Ray ray = {{0,0,0,1},{0,0,1,0}};
    Object sphere1;
    Color default_color = {0.8, 1.0, 0.6};
    Material mat;
    ray_CreateMaterial(&mat, &default_color, 0.1, 0.7, 0.2, 200.0);
    ray_CreateSphere(&sphere1, &mat);
    Intersection inter = {1.0, sphere1};
    Comps comps;
    world_PrepareComputations(&comps, &inter, &ray);

    Tuple4d pt = {0,0,1,1};
    Tuple4d vec = {0,0,-1,0};

    TEST_ASSERT_TRUE(comps.isHitFromInside);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&pt, &(comps.point)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&vec, &(comps.eyeV)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&vec, &(comps.normalV)));
}

void test_world_ShadeIntersection(void)
{
    World w;
    world_CreateDefault(&w);

    Ray ray = {{0,0,-5,1},{0,0,1,0}};
    Object obj = w.objects[0];
    Intersection inter = {4.0, obj};
    Comps comps;
    world_PrepareComputations(&comps, &inter, &ray);
    Color col;
    world_ShadeHit(&w, &comps, &col);

    Color expected = {0.38066, 0.47583, 0.2855};

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.red, col.red);    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.blue, col.blue);    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.green, col.green);    
}

void test_world_ShadeIntersectionFromInside(void)
{
    World w;
    world_CreateDefault(&w);
    PointLight light = {{0,0.25,0,1},{1,1,1}};
    w.lightSource = light;

    Ray ray = {{0,0,0,1},{0,0,1,0}};
    Object obj = w.objects[1];
    Intersection inter = {0.5, obj};
    Comps comps;
    world_PrepareComputations(&comps, &inter, &ray);
    Color col;
    world_ShadeHit(&w, &comps, &col);

    Color expected = {0.90498, 0.90498, 0.90498};

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.red, col.red);    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.blue, col.blue);    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected.green, col.green);    
}

void test_world_ColorAt_WhenRayMisses(void)
{
    World w;
    world_CreateDefault(&w);

    Ray ray = {{0,0,-5,1},{0,1,0,0}};
    Color c = {0,0,0};
    world_ColorAt(&w, &ray, &c);

    Color expected = {0,0,0};

    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &c));

}

void test_world_ColorAt_WhenRayHitsOuterSphere(void)
{
    World w;
    world_CreateDefault(&w);

    Ray ray = {{0,0,-5,1},{0,0,1,0}};
    Color c = {0,0,0};
    world_ColorAt(&w, &ray, &c);

    Color expected = {0.38066,0.47583,0.2855};

    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &c));

}

void test_world_ColorAt_WhenRayHitsInnerSphere(void)
{
    // DEFAULT WORLD + CHANGE IN AMBIENT (--> 1!)
    World w;
    world_CreateDefault(&w);
    w.objects[0].material.ambient = 1.0;
    w.objects[1].material.ambient = 1.0;

    // NEW TEST
    Ray ray = {{0,0,0.75,1},{0,0,-1,0}};
    Color c = {0,0,0};
    world_ColorAt(&w, &ray, &c);

    Color expected = w.objects[1].material.color;

    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &c));

}

void test_world_CreateViewTransform_DefaultOrientation(void)
{
    Tuple4d from = {0,0,0,1};
    Tuple4d to = {0,0,-1,1};
    Tuple4d up = {0,1,0,0};
    Matrix4d viewTrans;
    world_CreateViewTransform(&viewTrans, &from, &to, &up);

    Matrix4d expected = UNITY_TRANSFORM;

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &viewTrans));
}

void test_world_CreateViewTransform_InvertedOrientation(void)
{
    Tuple4d from = {0,0,0,1};
    Tuple4d to = {0,0,1,1};
    Tuple4d up = {0,1,0,0};
    Matrix4d viewTrans;
    world_CreateViewTransform(&viewTrans, &from, &to, &up);

    Matrix4d expected;
    transforms_GetScalingMatrix4d(&expected, -1, 1, -1);

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &viewTrans));
}

void test_world_CreateViewTransform_MovesTheWorld(void)
{
    Tuple4d from = {0,0,8,1};
    Tuple4d to = {0,0,0,1};
    Tuple4d up = {0,1,0,0};
    Matrix4d viewTrans;
    world_CreateViewTransform(&viewTrans, &from, &to, &up);

    Matrix4d expected;
    transforms_GetTranslationMatrix4d(&expected, 0, 0, -8);

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &viewTrans));
}

void test_world_CreateViewTransform_Arbitrary(void)
{
    Tuple4d from = {1,3,2,1};
    Tuple4d to = {4,-2,8,1};
    Tuple4d up = {1,1,0,0};
    Matrix4d viewTrans;
    world_CreateViewTransform(&viewTrans, &from, &to, &up);

    Matrix4d expected = {
        {-0.50709, 0.50709,  0.67612, -2.36643},
        { 0.76772, 0.60609,  0.12122, -2.82843},
        {-0.35857, 0.59761, -0.71714,  0.00000},
        { 0.00000, 0.00000,  0.00000,  1.00000}
    };

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &viewTrans));
}
#endif // TEST
