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
    Object s = {SPHERE, UNITY_TRANSFORM};
//    ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);

    Ray r = {{0,0,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 6.0, intersections.intersections[1].t);
}

void test_ray_IntersectSphereInTangent(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,1,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.0, intersections.intersections[1].t);
}

void test_ray_IntersectSphereMisses(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};;
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,2,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(0, intersections.count);
}

void test_ray_IntersectSphere_AndRayOriginatesAtItsCenter(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};;
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,0,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -1.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, intersections.intersections[1].t);    
}

void test_ray_IntersectSphereBehindRay(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};;
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,0,5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -6.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.0, intersections.intersections[1].t);
}

void test_ray_IntersectionSavesIntersectedObject(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};;
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
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
    Object sphere = {SPHERE, UNITY_TRANSFORM};
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
    Object sphere = {SPHERE, UNITY_TRANSFORM};
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
    Object sphere = {SPHERE, UNITY_TRANSFORM};
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
    Object sphere = {SPHERE, UNITY_TRANSFORM};
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

    ray_BubbleSortIntersections(&ints);
    float list[4] = {ints.intersections[0].t, ints.intersections[1].t, 
                    ints.intersections[2].t, ints.intersections[3].t, };
    float sorted[4] = {-3, 2, 5, 7};
    TEST_ASSERT_EQUAL_FLOAT_ARRAY(sorted, list, 4);

}

void test_ray_BubbleSortInts(void)
{
    int list[10] = {6,1,-4,3,8,2,1,3,4,-7};
    ray_BubbleSortIntegers(list, 10);
    int sorted[10] = {-7,-4,1,1,2,3,3,4,6,8};

    TEST_ASSERT_EQUAL_INT_ARRAY(sorted, list, 10);
}

void test_ray_TranslateRay(void)
{
    Ray r = {{1,2,3,1},{0,1,0,0}};
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 3, 4, 5);
    Ray r2;
    ray_Transform(&r, &r2, &transl);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&((Tuple4d){4, 6, 8, 1}), &(r2.origin)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&((Tuple4d){0, 1, 0, 0}), &(r2.direction)));
}

void test_ray_ScaleRay(void)
{
    Ray r = {{1,2,3,1},{0,1,0,0}};
    Matrix4d scale;
    transforms_GetScalingMatrix4d(&scale, 2, 3, 4);
    Ray r2;
    ray_Transform(&r, &r2, &scale);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&((Tuple4d){2, 6, 12, 1}), &(r2.origin)));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&((Tuple4d){0, 3, 0, 0}), &(r2.direction)));
}

void test_ray_SphereDefaultTransform(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Matrix4d identity_matrix = UNITY_TRANSFORM;

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&identity_matrix, &(sphere.transform)));
}

void test_ray_SphereChangeTransform(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 2, 3, 4);
    ray_ObjectSetTransform(&sphere, &transl);

    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&transl, &(sphere.transform)));   
}

void test_ray_IntersectionWithScaledSphere(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};
    Matrix4d scale;
    transforms_GetScalingMatrix4d(&scale, 2, 2, 2);
    ray_ObjectSetTransform(&s, &scale);
    Ray r = {{0,0,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(2, intersections.count);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 3.0, intersections.intersections[0].t);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 7.0, intersections.intersections[1].t);
}

void test_ray_DoesNotIntersectWithTranslatedSphere(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 5, 0, 0);
    ray_ObjectSetTransform(&s, &transl);
    Ray r = {{0,0,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(0, intersections.count);
}
#endif // TEST