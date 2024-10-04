#ifdef TEST

#include "unity.h"
#include <stdio.h>
#include "vecmath.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_vecmath_CreateTuple(void)
{
    Tuple t;
    vecmath_CreateTuple(&t, 4.3, -4.2, 3.1, 1.0);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.3, t.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.2, t.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 3.1, t.z);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, t.w);
    TEST_ASSERT_TRUE(vecmath_IsPoint(&t));
    TEST_ASSERT_FALSE(vecmath_IsVector(&t));
}

void test_vecmath_CreatePoint(void)
{
    Tuple t;
    vecmath_CreatePoint(&t, 4.3, -4.2, 3.1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.3, t.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.2, t.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 3.1, t.z);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, t.w);
    TEST_ASSERT_TRUE(vecmath_IsPoint(&t));
    TEST_ASSERT_FALSE(vecmath_IsVector(&t));
}

void test_vecmath_CreateVector(void)
{
    Tuple t;
    vecmath_CreateVector(&t, 4.3, -4.2, 3.1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4.3, t.x);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4.2, t.y);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 3.1, t.z);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, t.w);
    TEST_ASSERT_TRUE(vecmath_IsVector(&t));
    TEST_ASSERT_FALSE(vecmath_IsPoint(&t));
}

void test_vecmath_AreEqualTuples(void)
{
    Tuple t1, t2;
    vecmath_CreateTuple(&t1, 4.3, -4.2, 3.1, 1.0);
    vecmath_CreateTuple(&t2, 4.3, -4.2, 3.1, 1.0);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &t2));
}

void test_vecmath_AddTuples(void)
{
    Tuple t1, t2;
    Tuple expected;
    vecmath_CreateTuple(&t1, 3, -2, 5, 1);
    vecmath_CreateTuple(&t2, -2, 3, 1, 0);
    vecmath_CreateTuple(&expected, 1, 1, 6, 1);
    vecmath_AddTuples(&t1, &t2);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_TRUE(vecmath_IsPoint(&t1));
}

void test_vecmath_SubtractingPoints_CreatesVector(void)
{
    Tuple t1, t2;
    Tuple expected;
    vecmath_CreatePoint(&t1, 3, 2, 1);
    vecmath_CreatePoint(&t2, 5, 6, 7);
    vecmath_CreateVector(&expected, -2, -4, -6);
    vecmath_SubtractTuples(&t1, &t2);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_TRUE(vecmath_IsVector(&t1));
}

void test_vecmath_SubtractingVectorFromPoint_CreatesPoint(void)
{
    Tuple t1, t2;
    Tuple expected;
    vecmath_CreatePoint(&t1, 3, 2, 1);
    vecmath_CreateVector(&t2, 5, 6, 7);
    vecmath_CreatePoint(&expected, -2, -4, -6);
    vecmath_SubtractTuples(&t1, &t2);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_TRUE(vecmath_IsPoint(&t1));
}

void test_vecmath_SubtractingVectorFromVector_CreatesVector(void)
{
    Tuple t1, t2;
    Tuple expected;
    vecmath_CreateVector(&t1, 3, 2, 1);
    vecmath_CreateVector(&t2, 5, 6, 7);
    vecmath_CreateVector(&expected, -2, -4, -6);
    vecmath_SubtractTuples(&t1, &t2);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_TRUE(vecmath_IsVector(&t1));
}

void test_vecmath_SubtractingVectorFromNull_NegatesIt(void)
{
    Tuple t1, t2;
    Tuple expected;
    vecmath_CreateVector(&t1, 0, 0, 0);
    vecmath_CreateVector(&t2, 1, -2, 3);
    vecmath_CreateVector(&expected, -1, 2, -3);
    vecmath_SubtractTuples(&t1, &t2);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_TRUE(vecmath_IsVector(&t1));
}

void test_vecmath_NegateTuple(void)
{
    Tuple t1;
    Tuple expected;
    vecmath_CreateTuple(&t1, 1, -2, 3, -4);
    vecmath_CreateTuple(&expected, -1, 2, -3, 4);
    vecmath_NegateTuple(&t1);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
}

void test_vecmath_ScaleTuple(void)
{
    Tuple t1;
    float scalar = 3.5;
    Tuple expected;
    vecmath_CreateTuple(&t1, 1, -2, 3, -4);
    vecmath_CreateTuple(&expected, 3.5, -7, 10.5, -14);
    vecmath_ScaleTuple(&t1, scalar);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
}

void test_vecmath_ScaleTupleByFraction(void)
{
    Tuple t1;
    float scalar = 0.5;
    Tuple expected;
    vecmath_CreateTuple(&t1, 1, -2, 3, -4);
    vecmath_CreateTuple(&expected, 0.5, -1, 1.5, -2);
    vecmath_ScaleTuple(&t1, scalar);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
}

void test_vecmath_DivideTuple(void)
{
    Tuple t1;
    float scalar = 2;
    Tuple expected;
    vecmath_CreateTuple(&t1, 1, -2, 3, -4);
    vecmath_CreateTuple(&expected, 0.5, -1, 1.5, -2);
    vecmath_DivideTuple(&t1, scalar);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
}

void test_vecmath_Magnitude_x1(void)
{
    Tuple t1;
    float magnitude;
    float expected = 1;
    vecmath_CreateVector(&t1, 1, 0, 0);
//    printf("x:%f, y:%f, z:%f, w:%f", t1.x, t1.y, t1.z, t1.w);
    magnitude = vecmath_Magnitude(&t1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, magnitude);
}

void test_vecmath_Magnitude_y1(void)
{
    Tuple t1;
    float magnitude;
    float expected = 1;
    vecmath_CreateVector(&t1, 0, 1, 0);
    magnitude = vecmath_Magnitude(&t1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, magnitude);
}

void test_vecmath_Magnitude_z1(void)
{
    Tuple t1;
    float magnitude;
    float expected = 1;
    vecmath_CreateVector(&t1, 0, 0, 1);
    magnitude = vecmath_Magnitude(&t1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, magnitude);
}

void test_vecmath_Magnitude_123(void)
{
    Tuple t1;
    float magnitude;
    float expected = sqrt(14);
    vecmath_CreateVector(&t1, 1, 2, 3);
    magnitude = vecmath_Magnitude(&t1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, magnitude);
}

void test_vecmath_Magnitude_minus_123(void)
{
    Tuple t1;
    float magnitude;
    float expected = sqrt(14);
    vecmath_CreateVector(&t1, -1, -2, -3);
    magnitude = vecmath_Magnitude(&t1);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, magnitude);
}

void test_vecmath_Normalize_x4(void)
{
    Tuple t1, expected;
    vecmath_CreateVector(&t1, 4, 0, 0);
    vecmath_CreateVector(&expected, 1, 0, 0);
    vecmath_Normalize(&t1);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t1, &expected));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, vecmath_Magnitude(&t1));
}

void test_vecmath_Normalize_123(void)
{
    Tuple t, expected;
    vecmath_CreateVector(&t, 1, 2, 3);
    float length = vecmath_Magnitude(&t);
    vecmath_CreateVector(&expected, 1/length, 2/length, 3/length);
    vecmath_Normalize(&t);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&t, &expected));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, vecmath_Magnitude(&t));
}

void test_vecmath_DotProduct(void)
{
    Tuple t1, t2;
    float expected = 20;
    vecmath_CreateVector(&t1, 1, 2, 3);
    vecmath_CreateVector(&t2, 2, 3, 4);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, expected, vecmath_DotProduct(&t1, &t2));
}

void test_vecmath_CrossProduct(void)
{
    Tuple t1, t2, result1, result2, expected1, expected2;
    vecmath_CreateVector(&t1, 1, 2, 3);
    vecmath_CreateVector(&t2, 2, 3, 4);
    vecmath_CreateVector(&expected1, -1, 2, -1);
    vecmath_CreateVector(&expected2, 1, -2, 1);
    vecmath_CrossProduct(&result1, &t1, &t2);
    vecmath_CrossProduct(&result2, &t2, &t1);
//    vecmath_PrintTuple(&result1);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&result1, &expected1));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&result2, &expected2));
}

void test_vecmath_CreateMatrices(void)
{
    Matrix2d m2 = {
        {-3, 5},
        {1, -2}
    };
    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -3, m2[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5, m2[0][1]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1, m2[1][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -2, m2[1][1]);    
    
    Matrix3d m3 = {
        {-3, 5, 0},
        {1, -2, -7},
        {0, 1, 1}
    };
    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -3, m3[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -2, m3[1][1]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1, m3[2][2]);
    
    Matrix4d m4 = {
        {1, 2, 3, 4},
        {5.5, 6.5, 7.5, 8.5},
        {9, 10, 11, 12},
        {13.5, 14.5, 15.5, 16.5}
    };
    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1, m4[0][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 4, m4[0][3]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 5.5, m4[1][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 7.5, m4[1][2]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 11, m4[2][2]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 13.5, m4[3][0]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 15.5, m4[3][2]);

}

void test_vecmath_AreEqualMatrices(void)
{
    Matrix4d a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    Matrix4d b = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&a, &b));

    Matrix4d c = {
        {2, 3, 4, 5},
        {6, 7, 8, 9},
        {8, 7, 6, 5},
        {4, 3, 2, 1}
    };
    
    TEST_ASSERT_FALSE(vecmath_AreEqualMatrices4d(&a, &c));
}

void test_vecmath_MultiplyMatrices4d(void)
{
    Matrix4d a = {
        {1, 2, 3, 4},
        {5, 6, 7, 8},
        {9, 8, 7, 6},
        {5, 4, 3, 2}
    };
    Matrix4d b = {
        {-2, 1, 2, 3},
        {3, 2, 1, -1},
        {4, 3, 6, 5},
        {1, 2, 7, 8}
    };
    Matrix4d expected = {
        {20, 22, 50, 48},
        {44, 54, 114, 108},
        {40, 58, 110, 102},
        {16, 26, 46, 42}
    };

    vecmath_MultiplyMatrix4d(&a, &b);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &a));
}

void test_vecmath_MultiplyMatrix4dByTuple4d(void)
{
    Matrix4d m = {
        {1, 2, 3, 4},
        {2, 4, 4, 2},
        {8, 6, 4, 1},
        {0, 0, 0, 1}
    };

    Tuple a;
    vecmath_CreatePoint(&a, 1, 2, 3);
    Tuple expected; 
    vecmath_CreatePoint(&expected, 18, 24, 33);

    vecmath_MultiplyTupleByMatrix(&a, &m);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&expected, &a));
}

void test_vecmath_MultiplyTupleByIdentityMatrix(void)
{
    Matrix4d m = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    Tuple a;
    vecmath_CreateTuple(&a, 1, 2, 3, 4);
    Tuple expected; 
    vecmath_CreateTuple(&expected, 1, 2, 3, 4);

    vecmath_MultiplyTupleByMatrix(&a, &m);
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples(&expected, &a));
}

void test_vecmath_TransposeMatrix4d(void)
{
    Matrix4d m = {
        {0,9,3,0},
        {9,8,0,8},
        {1,8,5,3},
        {0,0,5,8}
    };
    Matrix4d expected = {
        {0,9,1,0},
        {9,8,8,0},
        {3,0,5,5},
        {0,8,3,8}
    };

    vecmath_TranssposeMatrix(&m);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &m));
}

void test_vecmath_TransposeIdentityIsIdentity(void)
{
    Matrix4d m = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    Matrix4d expected = {
        {1,0,0,0},
        {0,1,0,0},
        {0,0,1,0},
        {0,0,0,1}
    };
    vecmath_TranssposeMatrix(&m);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &m));
}

void test_vecmath_DeterminanteOfMatrix2d(void)
{
    Matrix2d m = {
        {1,5},
        {-3,2}
    };

    float res = vecmath_DeterminantMatrix2d(&m);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 17, res);
}

void test_vecmath_SubmatrixOfMatrix3dIsMatrix2d(void)
{
    Matrix3d m = {
        {1,5,0},
        {-3,2,7},
        {0,6,-3}
    };
    Matrix2d res = {{0,0},{0,0}};
    Matrix2d expected = {
        {-3,2},
        {0,6}
    };
    vecmath_SubmatrixOfMatrix3d(&m, &res, 0, 2);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices2d(&expected, &res));
}

void test_vecmath_SubmatrixOfMatrix4dIsMatrix3d(void)
{
    Matrix4d m = {
        {-6, 1, 1, 6},
        {-8, 5, 8, 6},
        {-1, 0, 8, 2},
        {-7, 1, -1, 1}
    };
    Matrix3d res = {{0,0,0},{0,0,0},{0,0,0}};
    Matrix3d expected = {
        {-6, 1, 6},
        {-8, 8, 6},
        {-7, -1, 1}
    };
    vecmath_SubmatrixOfMatrix4d(&m, &res, 2, 1);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices3d(&expected, &res));
}

void test_vecmath_MinorOfMatrix3d(void)
{
    Matrix3d m = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    };
    Matrix2d sub = {{0,0},{0,0}};
    vecmath_SubmatrixOfMatrix3d(&m, &sub, 1, 0);
    
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 25, vecmath_DeterminantMatrix2d(&sub));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 25, vecmath_MinorMatrix3d(&m, 1, 0));

}

void test_vecmath_CofactorOfMatrix3d(void)
{
    Matrix3d m = {
        {3, 5, 0},
        {2, -1, -7},
        {6, -1, 5}
    };

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -12, vecmath_MinorMatrix3d(&m, 0, 0));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -12, vecmath_CofactorMatrix3d(&m, 0, 0));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 25, vecmath_MinorMatrix3d(&m, 1, 0));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -25, vecmath_CofactorMatrix3d(&m, 1, 0));
}

void test_vecmath_DeterminantOfMatrix3d(void)
{
    Matrix3d m = {
        {1,2, 6},
        {-5, 8, -4},
        {2, 6, 4}
    };
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 56, vecmath_CofactorMatrix3d(&m, 0, 0));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 12, vecmath_CofactorMatrix3d(&m, 0, 1));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -46, vecmath_CofactorMatrix3d(&m, 0, 2));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -196, vecmath_DeterminantMatrix3d(&m));

}

void test_vecmath_DeterminantOfMatrix4d(void)
{
    Matrix4d m = {
        {-2, -8, 3, 5},
        {-3, 1, 7, 3},
        {1, 2, -9, 6},
        {-6, 7, 7, -9}
    };
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 690, vecmath_CofactorMatrix4d(&m, 0, 0));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 447, vecmath_CofactorMatrix4d(&m, 0, 1));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 210, vecmath_CofactorMatrix4d(&m, 0, 2));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 51, vecmath_CofactorMatrix4d(&m, 0, 3));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -4071, vecmath_DeterminantMatrix4d(&m));

}

void test_vecmath_IsInvertibleMatrix4d(void)
{
    Matrix4d m = {
        {6,4,4,4},
        {5,5,7,6},
        {4,-9,3,-7},
        {9,1,7,-6}
    };
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -2120, vecmath_DeterminantMatrix4d(&m));
    TEST_ASSERT_TRUE(vecmath_IsInvertibleMatrix4d(&m));
}

void test_vecmath_IsNotInvertibleMatrix4d(void)
{
    Matrix4d m = {
        {-4,2,-2,-3},
        {9,6,2,6},
        {0,-5,1,-5},
        {0,0,0,0}
    };
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0, vecmath_DeterminantMatrix4d(&m));
    TEST_ASSERT_FALSE(vecmath_IsInvertibleMatrix4d(&m));
}

void test_vecmath_InverseMatrix4d(void)
{
    Matrix4d a = {
        {-5, 2, 6, -8},
        {1, -5, 1, 8},
        {7, 7, -6, -7},
        {1, -3, 7, 4}
    };
    Matrix4d b = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    vecmath_InverseMatrix4d(&a, &b);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 532, vecmath_DeterminantMatrix4d(&a));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -160, vecmath_CofactorMatrix4d(&a, 2, 3));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -160.0/532.0, b[3][2]);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 105, vecmath_CofactorMatrix4d(&a, 3, 2));
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 105.0/532.0, b[2][3]);
    
    Matrix4d expected = {
        { 0.21805, 0.45113, 0.24060,-0.04511},
        {-0.80827,-1.45677,-0.44361, 0.52068},
        {-0.07895,-0.22368,-0.05263, 0.19737},
        {-0.52256,-0.81391,-0.30075, 0.30639}
    };
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &b));

    Matrix4d c = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    vecmath_FastInverseMatrix4d(&a, &c);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &c));
}

void test_vecmath_MoreInverseMatrix4d(void)
{
    Matrix4d a = {
        {8, -5, 9, 2},
        {7, 5, 6, 1},
        {-6, 0, 9, 6},
        {-3, 0, -9, -4}
    };
    Matrix4d b = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    vecmath_FastInverseMatrix4d(&a, &b);
    Matrix4d expected = {
        {-0.15385, -0.15385, -0.28205, -0.53846},
        {-0.07692,  0.12308,  0.02564,  0.03077},
        { 0.35897,  0.35897,  0.43590,  0.92308},
        {-0.69231, -0.69231, -0.76923, -1.92308}
    };
//    vecmath_PrintMatrix4d(&b);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &b));
}

void test_vecmath_EvenMoreInverseMatrix4d(void)
{
    Matrix4d a = {
        {9, 3, 0, 9},
        {-5, -2, -6, -3},
        {-4, 9, 6, 4},
        {-7, 6, 6, 2}
    };
    Matrix4d b = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    vecmath_FastInverseMatrix4d(&a, &b);
    Matrix4d expected = {
        {-0.04074,-0.07778, 0.14444,-0.22222},
        {-0.07778, 0.03333, 0.36667,-0.33333},
        {-0.02901,-0.14630,-0.10926, 0.12963},
        { 0.17778, 0.06667,-0.26667, 0.33333}
    };
//    vecmath_PrintMatrix4d(&b);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected, &b));
}

void test_vecmath_MultiplyProductByInverse(void)
{
    Matrix4d a = {
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    };
    Matrix4d b = {
        {8, 2, 2, 2},
        {3, -1, 7, 0},
        {7, 0, 5, 4},
        {6, -2, 0, 5}
    };
    Matrix4d c = {{0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0}};
    vecmath_MultiplyMatrix4d(&a, &b);
    vecmath_FastInverseMatrix4d(&b, &c);
    vecmath_MultiplyMatrix4d(&a, &c);
    Matrix4d expected_is_a = {
        {3, -9, 7, 3},
        {3, -8, 2, -9},
        {-4, 4, 4, 1},
        {-6, 5, -1, 1}
    };
    // vecmath_PrintMatrix4d(&a);
    TEST_ASSERT_TRUE(vecmath_AreEqualMatrices4d(&expected_is_a, &a));
}

#endif // TEST
