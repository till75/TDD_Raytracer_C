#include "projectile.h"
#include "vecmath.h"

void projectile_Create(Projectile* pr, Tuple* pos, Tuple* vel)
{
    pr->position = pos;
    pr->velocity = vel;
}

void projectile_CreateEnv(Environment* env, Tuple* g, Tuple* w)
{
    env->gravity = g;
    env->wind = w;
}

void projectile_tick(Projectile* projectile, Environment* env)
{
    vecmath_AddTuples(projectile->position, projectile->velocity);
    vecmath_AddTuples(projectile->velocity, env->gravity);
    vecmath_AddTuples(projectile->velocity, env->wind);
}