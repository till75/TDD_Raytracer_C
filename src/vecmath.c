#include "vecmath.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void vecmath_PrintTuple(Tuple* t)
{
   printf("x:%6.2f, y:%6.2f, z:%6.2f, w:%6.2f", t->x, t->y, t->z, t->w); 
}

void vecmath_PrintMatrix4d(Matrix4d* m)
{
    for(int r=0; r<4; r++)
        printf( "| %8.5f | %8.5f | %8.5f | %8.5f |\n", (*m)[r][0], (*m)[r][1], (*m)[r][2], (*m)[r][3]); 
}

void vecmath_CreateTuple(Tuple* pT, float x, float y, float z, float a)
{
    pT->x = x;
    pT->y = y;
    pT->z = z;
    pT->w = a;
}


void vecmath_CreatePoint(Tuple* pT, float x, float y, float z)
{
    pT->x = x;
    pT->y = y;
    pT->z = z;
    pT->w = 1.0;
}

void vecmath_CreateVector(Tuple* pT, float x, float y, float z)
{
    pT->x = x;
    pT->y = y;
    pT->z = z;
    pT->w = 0.0;
}

float vecmath_GetItem(Matrix4d* matrix, int x, int y)
{
    return *(matrix)[x][y];
}

bool vecmath_IsPoint(Tuple* t)
{
    return(fabsf(t->w - 1.0f) < EPSILON);
}

bool vecmath_IsVector(Tuple* t)
{
    return(fabsf(t->w) < EPSILON);
}

bool vecmath_AreEqualTuples(Tuple* t1, Tuple* t2)
{
    return (
        (fabsf(t1->x - t2->x) < EPSILON)
        &&
        (fabsf(t1->y - t2->y) < EPSILON)
        &&
        (fabsf(t1->z - t2->z) < EPSILON)
        &&
        (fabsf(t1->w - t2->w) < EPSILON)
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

void vecmath_AddTuples(Tuple* t1, Tuple* t2)
{
    t1->x += t2->x;
    t1->y += t2->y;
    t1->z += t2->z;
    t1->w += t2->w;
}

void vecmath_SubtractTuples(Tuple* t1, Tuple* t2)
{
    t1->x -= t2->x;
    t1->y -= t2->y;
    t1->z -= t2->z;
    t1->w -= t2->w;
}

void vecmath_NegateTuple(Tuple* t)
{
    t->x *= -1.0;
    t->y *= -1.0;
    t->z *= -1.0;
    t->w *= -1.0;
}

void vecmath_ScaleTuple(Tuple* t, float s)
{
    t->x *= s;
    t->y *= s;
    t->z *= s;
    t->w *= s;
}

void vecmath_DivideTuple(Tuple* t, float s)
{
    t->x /= s;
    t->y /= s;
    t->z /= s;
    t->w /= s;
}

float vecmath_Magnitude(Tuple* t)
{
    return sqrt(t->x*t->x + t->y*t->y + t->z*t->z + t->w*t->w);
}

void vecmath_Normalize(Tuple* t)
{
    float length = vecmath_Magnitude(t);
    vecmath_DivideTuple(t, length);
}

float vecmath_DotProduct(Tuple* t1, Tuple* t2)
{
    return t1->x*t2->x + t1->y*t2->y + t1->z*t2->z + t1->w*t2->w;
}

void vecmath_CrossProduct(Tuple* result, Tuple* t1, Tuple* t2)
{
    result->x = t1->y * t2->z - t1->z * t2->y;
    result->y = t1->z * t2->x - t1->x * t2->z;
    result->z = t1->x * t2->y - t1->y * t2->x;
    result->w = 0.0;
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

void vecmath_MultiplyTupleByMatrix(Tuple* ret, Matrix4d* m)
{
    Tuple t;
    vecmath_CreateTuple(&t, ret->x, ret->y, ret->z, ret->w);
    ret->x = (*m)[0][0] * t.x + (*m)[0][1] * t.y + (*m)[0][2] * t.z + (*m)[0][3] * t.w;
    ret->y = (*m)[1][0] * t.x + (*m)[1][1] * t.y + (*m)[1][2] * t.z + (*m)[1][3] * t.w;
    ret->z = (*m)[2][0] * t.x + (*m)[2][1] * t.y + (*m)[2][2] * t.z + (*m)[2][3] * t.w;
    ret->w = (*m)[3][0] * t.x + (*m)[3][1] * t.y + (*m)[3][2] * t.z + (*m)[3][3] * t.w;
}

void vecmath_TranssposeMatrix(Matrix4d* res) 
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
    vecmath_TranssposeMatrix(res);
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