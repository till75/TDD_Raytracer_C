#ifndef VECMATH_H
#define VECMATH_H

#include <stdbool.h>

#define UNITY_TRANSFORM {{1.0f,0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f,1.0f}}

static float EPSILON = 0.00001f;

typedef float Tuple4d[4];
typedef float Matrix2d[2][2];
typedef float Matrix3d[3][3];
typedef float Matrix4d[4][4];

void vecmath_PrintTuple4d(Tuple4d*);
bool vecmath_IsPointTuple4d(Tuple4d*);
bool vecmath_IsVectorTuple4d(Tuple4d*);
bool vecmath_AreEqualTuples4d(Tuple4d*, Tuple4d*);
void vecmath_AddTuples4d(Tuple4d*, Tuple4d*);
void vecmath_SubtractTuples4d(Tuple4d*, Tuple4d*);
void vecmath_NegateTuple4d(Tuple4d*);
void vecmath_ScaleTuple4d(Tuple4d*, float);
void vecmath_DivideTuple4d(Tuple4d*, float);
float vecmath_MagnitudeTuple4d(Tuple4d*);
void vecmath_NormalizeTuple4d(Tuple4d*);
float vecmath_DotProductTuple4d(Tuple4d*, Tuple4d*);
void vecmath_CrossProductTuple4d(Tuple4d*, Tuple4d*, Tuple4d*);
void vecmath_MultiplyTuple4dByMatrix4d(Tuple4d*, Matrix4d*);
void vecmath_PrintMatrix4d(Matrix4d*);
bool vecmath_AreEqualMatrices2d(Matrix2d*, Matrix2d*);
bool vecmath_AreEqualMatrices3d(Matrix3d*, Matrix3d*);
bool vecmath_AreEqualMatrices4d(Matrix4d*, Matrix4d*);
void vecmath_MultiplyMatrix4d(Matrix4d*, Matrix4d*);
void vecmath_TranssposeMatrix4d(Matrix4d*);
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
void vecmath_CopyTuple4d(Tuple4d*, Tuple4d*);
void vecmath_CopyMatrix4d(Matrix4d*, Matrix4d*);
#endif // VECMATH_H