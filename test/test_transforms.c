#ifdef TEST

#include "unity.h"

#include "transforms.h"
#include "vecmath.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_transforms_GetTranslationMatrix4d(void)
{
    Matrix4d transl = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetTranslationMatrix4d(&transl, 5, -3, 2);
    Tuple4d p = {-3, 4, 5, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p, &transl);
    Tuple4d expected = {2, 1, 7, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_TranslationWithInverse_BackToStart(void)
{
    Matrix4d transl = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d inverse = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetTranslationMatrix4d(&transl, 5, -3, 2);
    Tuple4d p = {-3, 4, 5, 1};  // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p, &transl);
    vecmath_InverseMatrix4d(&transl, &inverse);
    vecmath_MultiplyTuple4dByMatrix4d(&p, &inverse);
    Tuple4d expected = {-3, 4, 5, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_VectorUnchangedByTranslation(void)
{
    Matrix4d transl = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetTranslationMatrix4d(&transl, 5, -3, 2);
    Tuple4d p = {-3, 4, 5, 0}; // Vector!
    vecmath_MultiplyTuple4dByMatrix4d(&p, &transl);
    Tuple4d expected = {-3, 4, 5, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_GetScalingMatrix4d(void)
{
    Matrix4d scale = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetScalingMatrix4d(&scale, 2, 3, 4);
    Tuple4d p = {-4, 6, 8, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p, &scale);
    Tuple4d expected = {-8, 18, 32, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_VectorAffectedByScaling(void)
{
    Matrix4d scale = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetScalingMatrix4d(&scale, 2, 3, 4);
    Tuple4d p = {-4, 6, 8, 0}; // Vector
    vecmath_MultiplyTuple4dByMatrix4d(&p, &scale);
    Tuple4d expected = {-8, 18, 32, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_ScalingWithInverse_BackToStart(void)
{
    Matrix4d scale = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d inverse = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetScalingMatrix4d(&scale, 2, 3, 4);
    Tuple4d p = {-3, 6, 8, 0};  // Vector
    vecmath_MultiplyTuple4dByMatrix4d(&p, &scale);
    vecmath_InverseMatrix4d(&scale, &inverse);
    vecmath_MultiplyTuple4dByMatrix4d(&p, &inverse);
    Tuple4d expected = {-3, 6, 8, 0};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}

void test_transforms_ScalingWithMinusOneIsReflection(void)
{
    Matrix4d scale = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetScalingMatrix4d(&scale, -1, 1, 1);
    Tuple4d p = {2, 3, 4, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p, &scale);
    Tuple4d expected = {-2, 3, 4, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected, &p));
}
#endif // TEST
