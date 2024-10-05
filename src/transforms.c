#include "transforms.h"
#include "vecmath.h"
#include <math.h>

void transforms_GetTranslationMatrix4d(Matrix4d* res, float x, float y, float z) 
{
    (*res)[0][0] = 1; (*res)[0][1] = 0; (*res)[0][2] = 0; (*res)[0][3] = x; 
    (*res)[1][0] = 0; (*res)[1][1] = 1; (*res)[1][2] = 0; (*res)[1][3] = y; 
    (*res)[2][0] = 0; (*res)[2][1] = 0; (*res)[2][2] = 1; (*res)[2][3] = z; 
    (*res)[3][0] = 0; (*res)[3][1] = 0; (*res)[3][2] = 0; (*res)[3][3] = 1; 
}

void transforms_GetScalingMatrix4d(Matrix4d* res, float x, float y, float z) 
{
    (*res)[0][0] = x; (*res)[0][1] = 0; (*res)[0][2] = 0; (*res)[0][3] = 0; 
    (*res)[1][0] = 0; (*res)[1][1] = y; (*res)[1][2] = 0; (*res)[1][3] = 0; 
    (*res)[2][0] = 0; (*res)[2][1] = 0; (*res)[2][2] = z; (*res)[2][3] = 0; 
    (*res)[3][0] = 0; (*res)[3][1] = 0; (*res)[3][2] = 0; (*res)[3][3] = 1; 
}

void transforms_GetRotationXMatrix4d(Matrix4d* res, float rad)
{
    float s = (float)sin((double)rad);
    float c = (float)cos((double)rad);
    (*res)[0][0] = 1; (*res)[0][1] = 0; (*res)[0][2] = 0; (*res)[0][3] = 0; 
    (*res)[1][0] = 0; (*res)[1][1] = c; (*res)[1][2] =-s; (*res)[1][3] = 0; 
    (*res)[2][0] = 0; (*res)[2][1] = s; (*res)[2][2] = c; (*res)[2][3] = 0; 
    (*res)[3][0] = 0; (*res)[3][1] = 0; (*res)[3][2] = 0; (*res)[3][3] = 1; 
}

void transforms_GetRotationYMatrix4d(Matrix4d* res, float rad)
{
    float s = (float)sin((double)rad);
    float c = (float)cos((double)rad);
    (*res)[0][0] = c; (*res)[0][1] = 0; (*res)[0][2] = s; (*res)[0][3] = 0; 
    (*res)[1][0] = 0; (*res)[1][1] = 1; (*res)[1][2] = 0; (*res)[1][3] = 0; 
    (*res)[2][0] =-s; (*res)[2][1] = 0; (*res)[2][2] = c; (*res)[2][3] = 0; 
    (*res)[3][0] = 0; (*res)[3][1] = 0; (*res)[3][2] = 0; (*res)[3][3] = 1; 
}

void transforms_GetRotationZMatrix4d(Matrix4d* res, float rad)
{
    float s = (float)sin((double)rad);
    float c = (float)cos((double)rad);
    (*res)[0][0] = c; (*res)[0][1] =-s; (*res)[0][2] = 0; (*res)[0][3] = 0; 
    (*res)[1][0] = s; (*res)[1][1] = c; (*res)[1][2] = 0; (*res)[1][3] = 0; 
    (*res)[2][0] = 0; (*res)[2][1] = 0; (*res)[2][2] = 1; (*res)[2][3] = 0; 
    (*res)[3][0] = 0; (*res)[3][1] = 0; (*res)[3][2] = 0; (*res)[3][3] = 1; 
}

void transforms_GetShearingMatrix4d(Matrix4d* res, float x_y, float x_z, float y_x, float y_z, float z_x, float z_y)
{
    (*res)[0][0] =  1; (*res)[0][1] =x_y; (*res)[0][2] =x_z; (*res)[0][3] = 0; 
    (*res)[1][0] =y_x; (*res)[1][1] =  1; (*res)[1][2] =y_z; (*res)[1][3] = 0; 
    (*res)[2][0] =z_x; (*res)[2][1] =z_y; (*res)[2][2] =  1; (*res)[2][3] = 0; 
    (*res)[3][0] =  0; (*res)[3][1] =  0; (*res)[3][2] =  0; (*res)[3][3] = 1; 
}