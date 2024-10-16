
#ifndef WORLD_H
#define WORLD_H

#include "ray.h"

typedef struct 
{
    Object objects[MAX_OBJECTS];
    int numberOfObjects;
    PointLight* lightSource; 
} World;

void world_Create(World*);
int world_getNumberOfObjects(World*);
void world_CreateDefault(World*);
void world_addObject(Object*);
#endif // WORLD_H
