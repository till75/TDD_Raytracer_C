#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "vecmath.h"

typedef struct
{
    Tuple* position;
    Tuple* velocity;
} Projectile;

typedef struct
{
    Tuple* gravity;
    Tuple* wind;
} Environment;

void projectile_Create(Projectile*, Tuple*, Tuple*);
void projectile_CreateEnv(Environment*, Tuple*, Tuple*);
void projectile_tick(Projectile*, Environment*);
#endif // PROJECTILE_H
