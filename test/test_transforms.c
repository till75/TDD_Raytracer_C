#ifdef TEST

#include "unity.h"

#include "transforms.h"
#include "vecmath.h"
//#include <math.h>
#define M_PI 3.14159265358979323846

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

void test_transforms_GetRotationXMatrix4d(void)
{
    Matrix4d half_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d full_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetRotationXMatrix4d(&half_quarter, M_PI / 4.0);
    transforms_GetRotationXMatrix4d(&full_quarter, M_PI / 2.0);
    Tuple4d p1 = {0, 1, 0, 1}; // Point
    Tuple4d p2 = {0, 1, 0, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p1, &half_quarter);
    vecmath_MultiplyTuple4dByMatrix4d(&p2, &full_quarter);
    Tuple4d expected1 = {0, sqrt(2)/2, sqrt(2)/2, 1};
    Tuple4d expected2 = {0, 0, 1, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected1, &p1));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected2, &p2));
}

void test_transforms_InverseRotationRotatesInOppositeDirection(void)
{
    Matrix4d half_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d inverse_half_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetRotationXMatrix4d(&half_quarter, M_PI / 4.0);
    vecmath_InverseMatrix4d(&half_quarter, &inverse_half_quarter);
    Tuple4d p1 = {0, 1, 0, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p1, &inverse_half_quarter);
    Tuple4d expected1 = {0, sqrt(2)/2, -sqrt(2)/2, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected1, &p1));
}

void test_transforms_GetRotationYMatrix4d(void)
{
    Matrix4d half_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d full_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetRotationYMatrix4d(&half_quarter, M_PI / 4.0);
    transforms_GetRotationYMatrix4d(&full_quarter, M_PI / 2.0);
    Tuple4d p1 = {0, 0, 1, 1}; // Point
    Tuple4d p2 = {0, 0, 1, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p1, &half_quarter);
    vecmath_MultiplyTuple4dByMatrix4d(&p2, &full_quarter);
    Tuple4d expected1 = {sqrt(2)/2, 0, sqrt(2)/2, 1};
    Tuple4d expected2 = {1, 0, 0, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected1, &p1));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected2, &p2));
}

void test_transforms_GetRotationZMatrix4d(void)
{
    Matrix4d half_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    Matrix4d full_quarter = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    transforms_GetRotationZMatrix4d(&half_quarter, M_PI / 4.0);
    transforms_GetRotationZMatrix4d(&full_quarter, M_PI / 2.0);
    Tuple4d p1 = {0, 1, 0, 1}; // Point
    Tuple4d p2 = {0, 1, 0, 1}; // Point
    vecmath_MultiplyTuple4dByMatrix4d(&p1, &half_quarter);
    vecmath_MultiplyTuple4dByMatrix4d(&p2, &full_quarter);
    Tuple4d expected1 = {-sqrt(2)/2, sqrt(2)/2, 0, 1};
    Tuple4d expected2 = {-1, 0, 0, 1};

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected1, &p1));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&expected2, &p2));
}
#endif // TEST
