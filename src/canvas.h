#ifndef CANVAS_H
#define CANVAS_H

#include "color.h"

#define CANVAS_HEIGHT 10;

typedef struct 
{
    Color* pixels;
    int width;
    int height;
} Canvas;

void canvas_Create(Canvas*, int, int);
void canvas_Destroy(Canvas*);
Color* canvas_GetColor(Canvas*, int, int);
void canvas_DrawPixel(Canvas*, Color*, int, int);
void canvas_HeaderToPPM(Canvas*, char*);
void canvas_PixelRowToPPM(Canvas*, char*, int);
void canvas_PixelsToPPM(Canvas*, char*);
void canvas_PixelsToPPMFile(Canvas*, char*);
#endif // CANVAS_H