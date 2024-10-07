#ifdef TEST

#include "unity.h"

#include "ray.h"
#include "vecmath.h"
#include "transforms.h"
#include <stdio.h>

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ray_CreateAndQuery(void)
{
    Tuple4d origin = {1,2,3,1};
    Tuple4d direction = {4,5,6,0};
    Ray r;
    ray_Create(&r, &origin, &direction);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(r.origin), &origin));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(r.direction), &direction));
}

#endif // TEST

void test_ray_Position(void)
{

    Ray r = {{2,3,4,1}, {1,0,0,0}};
    Tuple4d res1, res2, res3, res4;
    ray_Position(&r, &res1, 0);
    ray_Position(&r, &res2, 1);
    ray_Position(&r, &res3, -1);
    ray_Position(&r, &res4, 2.5);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(Tuple4d){2,3,4,1}, &res1));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(Tuple4d){3,3,4,1}, &res2));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(Tuple4d){1,3,4,1}, &res3));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(Tuple4d){4.5,3,4,1}, &res4));
}

void test_ray_IntersectSphereInTwoPoints(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 6.0, intersections.intersections[1].t);
}

void test_ray_IntersectSphereInTangent(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,1,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.0, intersections.intersections[1].t);
}

void test_ray_IntersectSphereMisses(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,2,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(0, intersections.count);
}

void test_ray_IntersectSphere_AndRayOriginatesAtItsCenter(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,0,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -1.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, intersections.intersections[1].t);    
}

void test_ray_IntersectSphereBehindRay(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -6.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.0, intersections.intersections[1].t);
}

void test_ray_IntersectionSavesIntersectedObject(void)
{
    Object s;
    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(SPHERE, intersections.intersections[0].object.type);
    TEST_ASSERT_EQUAL(SPHERE, intersections.intersections[1].object.type);
    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -6.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.0, intersections.intersections[1].t);
}

void test_ray_Hit_AllIntersectionsPositive(void)
{
    Object sphere = {SPHERE, {0,0,0,1}, 1};
    Intersection int1 = {1, sphere};
    Intersection int2 = {2, sphere};
    Intersections ints;
    ints.count = 2;
    ints.intersections[0] = int1;
    ints.intersections[1] = int2;
    Intersection result;
    ray_Hit(&ints, &result);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, int1.t, result.t);

}

void test_ray_Hit_SomeIntersectionsNegative(void)
{
    Object sphere = {SPHERE, {0,0,0,1}, 1};
    Intersection int1 = {-1, sphere};
    Intersection int2 = {1, sphere};
    Intersections ints;
    ints.count = 2;
    ints.intersections[0] = int1;
    ints.intersections[1] = int2;
    Intersection result;
    ray_Hit(&ints, &result);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, int2.t, result.t);
}

void test_ray_Hit_AllIntersectionsNegative(void)
{
    Object sphere = {SPHERE, {0,0,0,1}, 1};
    Intersection int1 = {-2, sphere};
    Intersection int2 = {-1, sphere};
    Intersections ints;
    ints.count = 2;
    ints.intersections[0] = int1;
    ints.intersections[1] = int2;
    Intersection result;
    ray_Hit(&ints, &result);

    TEST_ASSERT_EQUAL(OBJ_NONE, result.object.type);
}

void test_ray_Hit_AlwaysLowestNonNegative(void)
{
    Object sphere = {SPHERE, {0,0,0,1}, 1};
    Intersection int1 = {5, sphere};
    Intersection int2 = {7, sphere};
    Intersection int3 = {-3, sphere};
    Intersection int4 = {2, sphere};
    Intersections ints;
    ints.count = 4;
    ints.intersections[0] = int1;
    ints.intersections[1] = int2;
    ints.intersections[2] = int3;
    ints.intersections[3] = int4;
    Intersection result;
    ray_Hit(&ints, &result);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, int4.t, result.t);
}