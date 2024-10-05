#ifndef TRANSFORMS_H
#define TRANSFORMS_H

#include "vecmath.h"

#endif // TRANSFORMS_H

void transforms_GetTranslationMatrix4d(Matrix4d*, float, float, float);
void transforms_GetScalingMatrix4d(Matrix4d*, float, float, float);
void transforms_GetRotationXMatrix4d(Matrix4d*, float);
void transforms_GetRotationYMatrix4d(Matrix4d*, float);
void transforms_GetRotationZMatrix4d(Matrix4d*, float);
void transforms_GetShearingMatrix4d(Matrix4d*, float, float, float, float, float, float);