#include "color.h"
#include <stdio.h>
#include <math.h>

void color_Create(Color* pC, float r, float g, float b)
{
    pC->red = r;
    pC->green = g;
    pC->blue = b;
}

void color_AddColors(Color* pC1, Color* pC2)
{
    pC1->red += pC2->red;
    pC1->green += pC2->green;
    pC1->blue += pC2->blue;
}

void color_SubtractColors(Color* pC1, Color* pC2)
{
    pC1->red -= pC2->red;
    pC1->green -= pC2->green;
    pC1->blue -= pC2->blue;
}

void color_MultiplyColors(Color* pC1, Color* pC2)
{
    pC1->red *= pC2->red;
    pC1->green *= pC2->green;
    pC1->blue *= pC2->blue;
}

void color_ScaleColor(Color* pC, float s)
{
    pC->red *= s;
    pC->green *= s;
    pC->blue *= s;
}
static int color_toInt8(float c)
{
    if (c<=0.0)
        return 0;
    else if (c>=1.0)
        return 255;
    else
        return (int)round(c*255.0);
}

void color_toPPM(Color* color, char* ppm)
{
    sprintf(ppm, "%d %d %d", 
        color_toInt8(color->red),
        color_toInt8(color->green),
        color_toInt8(color->blue)
        );
}
