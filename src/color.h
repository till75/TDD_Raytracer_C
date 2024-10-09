#ifndef COLOR_H
#define COLOR_H

#include <stdbool.h>

typedef struct 
{
    float red;
    float green;
    float blue;
} Color;

void color_Create(Color*, float, float, float);
void color_AddColors(Color*, Color*);
void color_SubtractColors(Color*, Color*);
void color_MultiplyColors(Color*, Color*);
void color_ScaleColor(Color*, float);
void color_toPPM(Color*, char*);
bool color_AreEqualColors(Color*, Color*);
#endif // COLOR_H
