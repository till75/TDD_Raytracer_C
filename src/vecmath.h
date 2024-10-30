#ifndef VECMATH_H
#define VECMATH_H

#include <stdbool.h>

#define M_PI 3.14159265358979323846
#define UNITY_TRANSFORM {{1.0f,0.0f,0.0f,0.0f},{0.0f,1.0f,0.0f,0.0f},{0.0f,0.0f,1.0f,0.0f},{0.0f,0.0f,0.0f,1.0f}}

static float EPSILON = 0.00001f;

/**
 * 4 element array used for 3D vectors and points.
 * @note First 3 elements correspond to x, y, z. Last element is 0 for vectors and 1 for points.
 */
typedef float Tuple4d[4];

typedef float Matrix2d[2][2];
typedef float Matrix3d[3][3];
typedef float Matrix4d[4][4];

void vecmath_PrintTuple4d(Tuple4d*);
bool vecmath_IsPointTuple4d(Tuple4d*);
bool vecmath_IsVectorTuple4d(Tuple4d*);
bool vecmath_AreEqualTuples4d(Tuple4d*, Tuple4d*);
void vecmath_AddTuples4d(Tuple4d* result, Tuple4d* to_be_added);
void vecmath_SubtractTuples4d(Tuple4d* result, Tuple4d* to_be_subtracted);
void vecmath_NegateTuple4d(Tuple4d*);
void vecmath_ScaleTuple4d(Tuple4d* result, float factor);
void vecmath_DivideTuple4d(Tuple4d* result, float divisor);
float vecmath_MagnitudeTuple4d(Tuple4d*);
void vecmath_NormalizeTuple4d(Tuple4d*);
float vecmath_DotProductTuple4d(Tuple4d* a, Tuple4d* b);
void vecmath_CrossProductTuple4d(Tuple4d* result, Tuple4d* a, Tuple4d* b);
void vecmath_MultiplyTuple4dByMatrix4d(Tuple4d* result, Matrix4d* m);
void vecmath_PrintMatrix4d(Matrix4d*);
bool vecmath_AreEqualMatrices2d(Matrix2d*, Matrix2d*);
bool vecmath_AreEqualMatrices3d(Matrix3d*, Matrix3d*);
bool vecmath_AreEqualMatrices4d(Matrix4d*, Matrix4d*);
void vecmath_MultiplyMatrix4d(Matrix4d* result, Matrix4d* multiplier);
void vecmath_TranssposeMatrix4d(Matrix4d*);
float vecmath_DeterminantMatrix2d(Matrix2d*);
void vecmath_SubmatrixOfMatrix3d(Matrix3d* source, Matrix2d* result, int excl_row, int excl_col);
void vecmath_SubmatrixOfMatrix4d(Matrix4d* source, Matrix3d* result, int excl_row, int excl_col);
float vecmath_MinorMatrix3d(Matrix3d*, int row, int column);
float vecmath_CofactorMatrix3d(Matrix3d*, int row, int column);
float vecmath_DeterminantMatrix3d(Matrix3d*);
float vecmath_CofactorMatrix4d(Matrix4d*, int row, int column);
float vecmath_DeterminantMatrix4d(Matrix4d*);
bool vecmath_IsInvertibleMatrix4d(Matrix4d*);
void vecmath_InverseMatrix4d(Matrix4d* input, Matrix4d* result);
void vecmath_FastInverseMatrix4d(Matrix4d* input, Matrix4d* result);
void vecmath_ScaleMatrix4d(Matrix4d* m, float factor);
void vecmath_CopyTuple4d(Tuple4d* source, Tuple4d* destination);
void vecmath_CopyMatrix4d(Matrix4d* source, Matrix4d* destination);
#endif // VECMATH_H