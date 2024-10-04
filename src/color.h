#ifndef COLOR_H
#define COLOR_H

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
#endif // COLOR_H
