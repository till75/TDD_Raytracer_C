#ifndef VECMATH_H
#define VECMATH_H

#include <stdbool.h>

static float EPSILON = 0.00001f;

typedef struct 
{
    float x;
    float y;
    float z;
    float w;
} Tuple;

// typedef struct 
// {
//     float rows[4][4];
// } Matrix4d;

typedef float Matrix2d[2][2];
typedef float Matrix3d[3][3];
typedef float Matrix4d[4][4];

void vecmath_PrintTuple(Tuple*);
void vecmath_PrintMatrix4d(Matrix4d*);
void vecmath_CreateTuple(Tuple*, float, float, float, float);
void vecmath_CreatePoint(Tuple*, float, float, float);
void vecmath_CreateVector(Tuple*, float, float, float);
//void vecmath_CreateMatrix4d(Matrix4d*, float*);
float vecmath_GetItem(Matrix4d*, int, int);
bool vecmath_IsPoint(Tuple*);
bool vecmath_IsVector(Tuple*);
bool vecmath_AreEqualTuples(Tuple*, Tuple*);
bool vecmath_AreEqualMatrices2d(Matrix2d*, Matrix2d*);
bool vecmath_AreEqualMatrices3d(Matrix3d*, Matrix3d*);
bool vecmath_AreEqualMatrices4d(Matrix4d*, Matrix4d*);
void vecmath_AddTuples(Tuple*, Tuple*);
void vecmath_SubtractTuples (Tuple*, Tuple*);
void vecmath_NegateTuple(Tuple*);
void vecmath_ScaleTuple(Tuple*, float);
void vecmath_DivideTuple(Tuple*, float);
float vecmath_Magnitude(Tuple*);
void vecmath_Normalize(Tuple*);
float vecmath_DotProduct(Tuple*, Tuple*);
void vecmath_CrossProduct(Tuple*, Tuple*, Tuple*);
void vecmath_MultiplyMatrix4d(Matrix4d*, Matrix4d*);
void vecmath_MultiplyTupleByMatrix(Tuple*, Matrix4d*);
void vecmath_TranssposeMatrix(Matrix4d*);
float vecmath_DeterminantMatrix2d(Matrix2d*);
void vecmath_SubmatrixOfMatrix3d(Matrix3d*, Matrix2d*, int, int);
void vecmath_SubmatrixOfMatrix4d(Matrix4d*, Matrix3d*, int, int);
float vecmath_MinorMatrix3d(Matrix3d*, int, int);
float vecmath_CofactorMatrix3d(Matrix3d*, int, int);
float vecmath_DeterminantMatrix3d(Matrix3d*);
float vecmath_CofactorMatrix4d(Matrix4d*, int, int);
float vecmath_DeterminantMatrix4d(Matrix4d*);
bool vecmath_IsInvertibleMatrix4d(Matrix4d*);
void vecmath_InverseMatrix4d(Matrix4d*, Matrix4d*);
void vecmath_FastInverseMatrix4d(Matrix4d*, Matrix4d*);
void vecmath_ScaleMatrix4d(Matrix4d*, float);
#endif // VECMATH_H