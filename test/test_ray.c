#ifdef TEST

#include "unity.h"

#include "ray.h"
#include "vecmath.h"
#include "transforms.h"
#include "color.h"
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
    Object s = {SPHERE, UNITY_TRANSFORM};
    //ray_CreateSphere(&s, &(Tuple4d){0,0,0,1}, 1.0);
    Ray r = {{0,2,-5,1}, {0,0,1,0}};
    Intersections intersections;
    ray_IntersectSphere(&r, &s, &intersections);

    TEST_ASSERT_EQUAL(0, intersections.count);
}

void test_ray_IntersectSphere_AndRayOriginatesAtItsCenter(void)
{
    Object s = {SPHERE, UNITY_TRANSFORM};
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
    Object s = {SPHERE, UNITY_TRANSFORM};
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
    Object s = {SPHERE, UNITY_TRANSFORM};
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

void test_ray_CreateSphereNormalAtX1(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Tuple4d p = {1,0,0,1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {1,0,0,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
}

void test_ray_CreateSphereNormalAtY1(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Tuple4d p = {0,1,0,1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {0,1,0,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
}

void test_ray_CreateSphereNormalAtZ1(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Tuple4d p = {0,0,1,1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {0,0,1,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
}

void test_ray_CreateSphereNormalAtXYZ(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    float tmp = sqrt(3)/3.0;
    Tuple4d p = {tmp,tmp,tmp,1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {tmp,tmp,tmp,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, vecmath_MagnitudeTuple4d(&n));
}

void test_ray_CreateNormalOnTranslatedSphere(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Matrix4d transl;
    transforms_GetTranslationMatrix4d(&transl, 0, 1, 0);
    vecmath_CopyMatrix4d(&transl, &(sphere.transform));

    Tuple4d p = {0, 1.70711,-0.70711, 1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {0, 0.70711, -0.70711, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
}

void test_ray_CreateNormalOnScaledSphere(void)
{
    Object sphere = {SPHERE, UNITY_TRANSFORM};
    Matrix4d scale;
    transforms_GetScalingMatrix4d(&scale, 1, 0.5, 1);
    vecmath_CopyMatrix4d(&scale, &(sphere.transform));

    float tmp = sqrt(2.0)/2.0;
    Tuple4d p = {0, tmp, -tmp, 1};
    Tuple4d n = {0,0,0,0};
    ray_NormalAt(&sphere, &p, &n);
    Tuple4d exp = {0, 0.97014, -0.24254, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &n));
}

void test_ray_CreateReflectionAtNormal(void)
{
    Tuple4d v = {1, -1, 0, 0};
    Tuple4d n = {0, 1, 0, 0};
    Tuple4d r;
    ray_Reflect(&v, &n, &r);
    Tuple4d exp = {1,1,0,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &r));
}

void test_ray_CreateReflectionAtSlantedNormal(void)
{
    float tmp = sqrt(2.0)/2.0;
    Tuple4d v = {0, -1, 0, 0};
    Tuple4d n = {tmp, tmp, 0, 0};
    Tuple4d r;
    ray_Reflect(&v, &n, &r);
    Tuple4d exp = {1,0,0,0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&exp, &r));
}

void test_ray_PointLightHasPositionAndIntensity(void)
{
    Color intensity = {1, 1, 1};
    Tuple4d pos = {0,0,0,1};
    PointLight pl;
    ray_CreatePointLight(&pl, &pos, &intensity);
    Tuple4d expP = {0,0,0,1};
    Color expC = {1,1,1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expP, &(pl.pos)));
    TEST_ASSERT_TRUE(color_AreEqualColors(&expC, &(pl.intensity)));
}

void test_ray_CreateDefaultMaterial(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Color white = {1.0,1.0,1.0};

    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &(mat.color)));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.1, mat.ambient);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.9, mat.diffuse);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.9, mat.specular);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 200, mat.shininess);
}

void test_ray_SphereHasDefaultMaterial(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Object sphere;
    ray_CreateSphere(&sphere, &mat);
    Material expM;
    ray_CreateDefaultMaterial(&expM);

    TEST_ASSERT_EQUAL_MEMORY(&expM, &(sphere.material), sizeof(expM));
}

void test_ray_SphereHasAssignedMaterial(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    mat.ambient = 1;
    Object sphere;
    ray_CreateSphere(&sphere, &mat);
    Material expM;
    ray_CreateDefaultMaterial(&expM);
    expM.ambient = 1;

    TEST_ASSERT_EQUAL_MEMORY(&expM, &(sphere.material), sizeof(expM));
}

void test_ray_Lighting_EyeBetweenLightAndSurface(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Tuple4d pos = {0,0,0,1};
    Tuple4d eyeV = {0,0,-1,0};
    Tuple4d n = {0,0,-1,0};
    PointLight light;
    Tuple4d lightPos = {0,0,-10, 1};
    Color lightColor = {1, 1, 1};
    ray_CreatePointLight(&light, &lightPos, &lightColor);
    Color result;
    ray_Lighting(&result, &mat, &light, &pos, &eyeV, &n);

    Color expected = {1.9, 1.9, 1.9};
    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &result));
}

void test_ray_Lighting_EyeBetweenLightAndSurface_EyeOffsetAt45Degrees(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Tuple4d pos = {0,0,0,1};
    float tmp = sqrt(2)/2.0;
    Tuple4d eyeV = {0, tmp, -tmp, 0};
    Tuple4d n = {0,0,-1,0};
    PointLight light;
    Tuple4d lightPos = {0,0,-10, 1};
    Color lightColor = {1, 1, 1};
    ray_CreatePointLight(&light, &lightPos, &lightColor);
    Color result;
    ray_Lighting(&result, &mat, &light, &pos, &eyeV, &n);

    Color expected = {1.0, 1.0, 1.0};
    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &result));
}

void test_ray_Lighting_EyeOppositeSurface_LightAt45Degrees(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Tuple4d pos = {0,0,0,1};
    Tuple4d eyeV = {0,0,-1,0};
    Tuple4d n = {0,0,-1,0};
    PointLight light;
    Tuple4d lightPos = {0,10,-10, 1};
    Color lightColor = {1, 1, 1};
    ray_CreatePointLight(&light, &lightPos, &lightColor);
    Color result;
    ray_Lighting(&result, &mat, &light, &pos, &eyeV, &n);

    Color expected = {0.7364, 0.7364, 0.7364};
    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &result));
}

void test_ray_Lighting_EyeInPathOfReflectingVector(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Tuple4d pos = {0,0,0,1};
    float tmp = sqrt(2)/2.0;
    Tuple4d eyeV = {0, -tmp, -tmp, 0};
    Tuple4d n = {0,0,-1,0};//{0,0,-1,0};
    PointLight light;
    Tuple4d lightPos = {0,10,-10, 1};
    Color lightColor = {1, 1, 1};
    ray_CreatePointLight(&light, &lightPos, &lightColor);
    Color result;
    ray_Lighting(&result, &mat, &light, &pos, &eyeV, &n);

    Color expected = {1.6363853, 1.6363853, 1.6363853};
    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &result));
}

void test_ray_Lighting_LightBehindSurface(void)
{
    Material mat;
    ray_CreateDefaultMaterial(&mat);
    Tuple4d pos = {0,0,0,1};
    Tuple4d eyeV = {0,0,-1,0};
    Tuple4d n = {0,0,-1,0};
    PointLight light;
    Tuple4d lightPos = {0,0,10, 1};
    Color lightColor = {1, 1, 1};
    ray_CreatePointLight(&light, &lightPos, &lightColor);
    Color result;
    ray_Lighting(&result, &mat, &light, &pos, &eyeV, &n);

    Color expected = {0.1, 0.1, 0.1};
    TEST_ASSERT_TRUE(color_AreEqualColors(&expected, &result));
}
#endif // TEST