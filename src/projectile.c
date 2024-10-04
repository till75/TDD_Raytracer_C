#include "projectile.h"
#include "vecmath.h"

void projectile_Create(Projectile* pr, Tuple4d* pos, Tuple4d* vel)
{
    pr->position = pos;
    pr->velocity = vel;
}

void projectile_CreateEnv(Environment* env, Tuple4d* g, Tuple4d* w)
{
    env->gravity = g;
    env->wind = w;
}

void projectile_tick(Projectile* projectile, Environment* env)
{
    vecmath_AddTuples4d(projectile->position, projectile->velocity);
    vecmath_AddTuples4d(projectile->velocity, env->gravity);
    vecmath_AddTuples4d(projectile->velocity, env->wind);
}