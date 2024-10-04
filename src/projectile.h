#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vecmath.h"

typedef struct
{
    Tuple4d* position;
    Tuple4d* velocity;
} Projectile;

typedef struct
{
    Tuple4d* gravity;
    Tuple4d* wind;
} Environment;

void projectile_Create(Projectile*, Tuple4d*, Tuple4d*);
void projectile_CreateEnv(Environment*, Tuple4d*, Tuple4d*);
void projectile_tick(Projectile*, Environment*);
#endif // PROJECTILE_H
