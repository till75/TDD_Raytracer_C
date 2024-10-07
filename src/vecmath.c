#include "vecmath.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void vecmath_PrintTuple4d(Tuple4d* t)
{
    printf( "| %8.5f | %8.5f | %8.5f | %8.5f |\n", (*t)[0], (*t)[1], (*t)[2], (*t)[3]); 
}

void vecmath_PrintMatrix4d(Matrix4d* m)
{
    for(int r=0; r<4; r++)
        printf( "| %8.5f | %8.5f | %8.5f | %8.5f |\n", (*m)[r][0], (*m)[r][1], (*m)[r][2], (*m)[r][3]); 
}

bool vecmath_IsPointTuple4d(Tuple4d* t)
{
    return(fabsf((*t)[3] - 1.0f) < EPSILON);
}

bool vecmath_IsVectorTuple4d(Tuple4d* t)
{
    return(fabsf((*t)[3]) < EPSILON);
}

bool vecmath_AreEqualTuples4d(Tuple4d* t1, Tuple4d* t2)
{
    return (
        (fabsf((*t1)[0] - (*t2)[0]) < EPSILON)
        &&
        (fabsf((*t1)[1] - (*t2)[1]) < EPSILON)
        &&
        (fabsf((*t1)[2] - (*t2)[2]) < EPSILON)
        &&
        (fabsf((*t1)[3] - (*t2)[3]) < EPSILON)
    );
}

bool vecmath_AreEqualMatrices2d(Matrix2d* m1, Matrix2d* m2)
{
    return (
        (fabsf((*m1)[0][0] - (*m2)[0][0]) < EPSILON)
        &&
        (fabsf((*m1)[0][1] - (*m2)[0][1]) < EPSILON)
        &&
        (fabsf((*m1)[1][0] - (*m2)[1][0]) < EPSILON)
        &&
        (fabsf((*m1)[1][1] - (*m2)[1][1]) < EPSILON)
    );
}

bool vecmath_AreEqualMatrices3d(Matrix3d* m1, Matrix3d* m2)
{
    return (
        (fabsf((*m1)[0][0] - (*m2)[0][0]) < EPSILON)
        &&
        (fabsf((*m1)[0][1] - (*m2)[0][1]) < EPSILON)
        &&
        (fabsf((*m1)[0][2] - (*m2)[0][2]) < EPSILON)
        &&
        (fabsf((*m1)[1][0] - (*m2)[1][0]) < EPSILON)
        &&
        (fabsf((*m1)[1][1] - (*m2)[1][1]) < EPSILON)
        &&
        (fabsf((*m1)[1][2] - (*m2)[1][2]) < EPSILON)
        &&
        (fabsf((*m1)[2][0] - (*m2)[2][0]) < EPSILON)
        &&
        (fabsf((*m1)[2][1] - (*m2)[2][1]) < EPSILON)
        &&
        (fabsf((*m1)[2][2] - (*m2)[2][2]) < EPSILON)
    );
}

bool vecmath_AreEqualMatrices4d(Matrix4d* m1, Matrix4d* m2)
{
    return (
        (fabsf((*m1)[0][0] - (*m2)[0][0]) < EPSILON)
        &&
        (fabsf((*m1)[0][1] - (*m2)[0][1]) < EPSILON)
        &&
        (fabsf((*m1)[0][2] - (*m2)[0][2]) < EPSILON)
        &&
        (fabsf((*m1)[0][3] - (*m2)[0][3]) < EPSILON)
        &&
        (fabsf((*m1)[1][0] - (*m2)[1][0]) < EPSILON)
        &&
        (fabsf((*m1)[1][1] - (*m2)[1][1]) < EPSILON)
        &&
        (fabsf((*m1)[1][2] - (*m2)[1][2]) < EPSILON)
        &&
        (fabsf((*m1)[1][3] - (*m2)[1][3]) < EPSILON)
        &&
        (fabsf((*m1)[2][0] - (*m2)[2][0]) < EPSILON)
        &&
        (fabsf((*m1)[2][1] - (*m2)[2][1]) < EPSILON)
        &&
        (fabsf((*m1)[2][2] - (*m2)[2][2]) < EPSILON)
        &&
        (fabsf((*m1)[2][3] - (*m2)[2][3]) < EPSILON)
        &&
        (fabsf((*m1)[3][0] - (*m2)[3][0]) < EPSILON)
        &&
        (fabsf((*m1)[3][1] - (*m2)[3][1]) < EPSILON)
        &&
        (fabsf((*m1)[3][2] - (*m2)[3][2]) < EPSILON)
        &&
        (fabsf((*m1)[3][3] - (*m2)[3][3]) < EPSILON)
    );
}

void vecmath_AddTuples4d(Tuple4d* t1, Tuple4d* t2)
{
    (*t1)[0] += (*t2)[0];
    (*t1)[1] += (*t2)[1];
    (*t1)[2] += (*t2)[2];
    (*t1)[3] += (*t2)[3];
}

void vecmath_SubtractTuples4d(Tuple4d* t1, Tuple4d* t2)
{
    (*t1)[0] -= (*t2)[0];
    (*t1)[1] -= (*t2)[1];
    (*t1)[2] -= (*t2)[2];
    (*t1)[3] -= (*t2)[3];
}

void vecmath_NegateTuple4d(Tuple4d* t1)
{
    (*t1)[0] *= -1.0;
    (*t1)[1] *= -1.0;
    (*t1)[2] *= -1.0;
    (*t1)[3] *= -1.0;
}

void vecmath_ScaleTuple4d(Tuple4d* t1, float s)
{
    (*t1)[0] *= s;
    (*t1)[1] *= s;
    (*t1)[2] *= s;
    (*t1)[3] *= s;
}

void vecmath_DivideTuple4d(Tuple4d* t1, float s)
{
    (*t1)[0] /= s;
    (*t1)[1] /= s;
    (*t1)[2] /= s;
    (*t1)[3] /= s;
}

float vecmath_MagnitudeTuple4d(Tuple4d* t)
{
    return sqrt((*t)[0] * (*t)[0] + (*t)[1] * (*t)[1] + (*t)[2] * (*t)[2] + (*t)[3] * (*t)[3]);
}

void vecmath_NormalizeTuple4d(Tuple4d* t)
{
    float length = vecmath_MagnitudeTuple4d(t);
    vecmath_DivideTuple4d(t, length);
}

float vecmath_DotProductTuple4d(Tuple4d* t1, Tuple4d* t2)
{
    return (*t1)[0]*(*t2)[0] + (*t1)[1]*(*t2)[1] + (*t1)[2]*(*t2)[2] + (*t1)[3]*(*t2)[3];
}

void vecmath_CrossProductTuple4d(Tuple4d* result, Tuple4d* t1, Tuple4d* t2)
{
    (*result)[0] = (*t1)[1] * (*t2)[2] - (*t1)[2] * (*t2)[1];
    (*result)[1] = (*t1)[2] * (*t2)[0] - (*t1)[0] * (*t2)[2];
    (*result)[2] = (*t1)[0] * (*t2)[1] - (*t1)[1] * (*t2)[0];
    (*result)[3] = 0.0;
}

void vecmath_MultiplyMatrix4d(Matrix4d* res, Matrix4d* m2)
{
    Matrix4d tmp =  {
        {(*res)[0][0],(*res)[0][1],(*res)[0][2],(*res)[0][3]}, 
        {(*res)[1][0],(*res)[1][1],(*res)[1][2],(*res)[1][3]}, 
        {(*res)[2][0],(*res)[2][1],(*res)[2][2],(*res)[2][3]}, 
        {(*res)[3][0],(*res)[3][1],(*res)[3][2],(*res)[3][3]}, 
    };
    for (int r = 0; r<4; r++)
    {
        for (int c = 0; c<4; c++)
        {
            (*res)[r][c] =
                tmp[r][0] * (*m2)[0][c] +
                tmp[r][1] * (*m2)[1][c] +
                tmp[r][2] * (*m2)[2][c] +
                tmp[r][3] * (*m2)[3][c];
        }
    }
}

void vecmath_MultiplyTuple4dByMatrix4d(Tuple4d* ret, Matrix4d* m)
{
    Tuple4d t = {(*ret)[0], (*ret)[1], (*ret)[2], (*ret)[3]};
    (*ret)[0] = (*m)[0][0] * t[0] + (*m)[0][1] * t[1] + (*m)[0][2] * t[2] + (*m)[0][3] * t[3];
    (*ret)[1] = (*m)[1][0] * t[0] + (*m)[1][1] * t[1] + (*m)[1][2] * t[2] + (*m)[1][3] * t[3];
    (*ret)[2] = (*m)[2][0] * t[0] + (*m)[2][1] * t[1] + (*m)[2][2] * t[2] + (*m)[2][3] * t[3];
    (*ret)[3] = (*m)[3][0] * t[0] + (*m)[3][1] * t[1] + (*m)[3][2] * t[2] + (*m)[3][3] * t[3];
}

void vecmath_TranssposeMatrix4d(Matrix4d* res) 
{
    float t;
    t = (*res)[0][1]; (*res)[0][1] = (*res)[1][0]; (*res)[1][0] = t;
    t = (*res)[0][2]; (*res)[0][2] = (*res)[2][0]; (*res)[2][0] = t;
    t = (*res)[0][3]; (*res)[0][3] = (*res)[3][0]; (*res)[3][0] = t;

    t = (*res)[1][2]; (*res)[1][2] = (*res)[2][1]; (*res)[2][1] = t;
    t = (*res)[1][3]; (*res)[1][3] = (*res)[3][1]; (*res)[3][1] = t;

    t = (*res)[2][3]; (*res)[2][3] = (*res)[3][2]; (*res)[3][2] = t;
}

float vecmath_DeterminantMatrix2d(Matrix2d* m)
{
    return (*m)[0][0] * (*m)[1][1] - (*m)[0][1] * (*m)[1][0];
}

void vecmath_SubmatrixOfMatrix3d(Matrix3d* m, Matrix2d* res, int excl_row, int excl_col)
{
    int skipped_rows = 0;
    int skipped_cols = 0;
    for (int r=0; r<3; r++)
    {
        if (r == excl_row)
        {
            skipped_rows++;
        }
        else
        {
            for (int c=0; c<3; c++)
            {
                if (c == excl_col)
                {
                    skipped_cols++;
                }
                else
                {
                    (*res)[r-skipped_rows][c-skipped_cols] = (*m)[r][c];
                }
            }
            skipped_cols = 0;
        }
    }
}

void vecmath_SubmatrixOfMatrix4d(Matrix4d* m, Matrix3d* res, int excl_row, int excl_col)
{
    int skipped_rows = 0;
    int skipped_cols = 0;
    for (int r=0; r<4; r++)
    {
        if (r == excl_row)
        {
            skipped_rows++;
        }
        else
        {
            for (int c=0; c<4; c++)
            {
                if (c == excl_col)
                {
                    skipped_cols++;
                }
                else
                {
                    (*res)[r-skipped_rows][c-skipped_cols] = (*m)[r][c];
                }
            }
            skipped_cols = 0;
        }
    }
}

float vecmath_MinorMatrix3d(Matrix3d* m, int r, int c)
{
    Matrix2d sub = {{0,0},{0,0}};
    vecmath_SubmatrixOfMatrix3d(m, &sub, r, c);
    return vecmath_DeterminantMatrix2d(&sub);
}

float vecmath_CofactorMatrix3d(Matrix3d* m, int r, int c)
{
    Matrix2d sub = {{0,0},{0,0}};
    vecmath_SubmatrixOfMatrix3d(m, &sub, r, c);
    if ((r+c)%2 == 0)
        return vecmath_DeterminantMatrix2d(&sub);
    else
        return -vecmath_DeterminantMatrix2d(&sub);
}

float vecmath_DeterminantMatrix3d(Matrix3d* m)
{
    float result = 0;
    for (int c=0; c<3; c++)
    {
        result += (*m)[0][c] * vecmath_CofactorMatrix3d(m, 0, c);
    }
    return result;
}

float vecmath_CofactorMatrix4d(Matrix4d* m, int r, int c)
{
    Matrix3d sub = {{0,0,0},{0,0,0},{0,0,0}};
    vecmath_SubmatrixOfMatrix4d(m, &sub, r, c);
    if ((r+c)%2 == 0)
        return vecmath_DeterminantMatrix3d(&sub);
    else
        return -vecmath_DeterminantMatrix3d(&sub);    
}

float vecmath_DeterminantMatrix4d(Matrix4d* m)
{
    float result = 0;
    for (int c=0; c<4; c++)
    {
        result += (*m)[0][c] * vecmath_CofactorMatrix4d(m, 0, c);
    }
    return result;
}

bool vecmath_IsInvertibleMatrix4d(Matrix4d* m)
{
    return (fabsf(vecmath_DeterminantMatrix4d(m)) > EPSILON);
}

void vecmath_ScaleMatrix4d(Matrix4d* m, float s)
{
    for (int r=0; r<4; r++)
        for(int c=0; c<4; c++)
            (*m)[r][c] *= s;
}

void vecmath_InverseMatrix4d(Matrix4d* m, Matrix4d* res)
{
    if (!vecmath_IsInvertibleMatrix4d(m))
        return;
    float det = vecmath_DeterminantMatrix4d(m);
    for (int r=0; r<4; r++)
    {
        for(int c=0; c<4; c++)
        {
            (*res)[r][c] = vecmath_CofactorMatrix4d(m, r, c);
        }
    }
    vecmath_TranssposeMatrix4d(res);
    vecmath_ScaleMatrix4d(res, 1.0/det);
}

void vecmath_FastInverseMatrix4d(Matrix4d* m, Matrix4d* res)
{
    if (!vecmath_IsInvertibleMatrix4d(m))
        return;
    float det = vecmath_DeterminantMatrix4d(m);
    for (int r=0; r<4; r++)
    {
        for(int c=0; c<4; c++)
        {
            (*res)[c][r] = vecmath_CofactorMatrix4d(m, r, c) / det;
        }
    }
}