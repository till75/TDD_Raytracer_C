#define TEST

#include "canvas.h"
#include "color.h"
#include "vecmath.h"
#include <stdio.h>


void main()
{
    Canvas canvas;
    Color c1, c2, c3;
    color_Create(&c1, 1.5, 0, 0);
    color_Create(&c2, 0, 0.5, 0);
    color_Create(&c3, -0.5, 0, 1);
    int dim_x = 5;
    int dim_y = 3;
    canvas_Create(&canvas, dim_x, dim_y);

    canvas_DrawPixel(&canvas, &c1, 0, 0);
    canvas_DrawPixel(&canvas, &c2, 2, 1);
    canvas_DrawPixel(&canvas, &c3, 4, 2);

    // 3 components per color, 4 byte ('255 ') per component
    char pixelPPM[dim_x * dim_y * 3 * 4 + 1]; 
    pixelPPM[0] = '\0';
    canvas_PixelsToPPM(&canvas, pixelPPM);
    printf("Pixel data is\n%s", pixelPPM);

    //TEST_ASSERT_EQUAL_STRING("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0", pixelPPM);
    canvas_Destroy(&canvas);
}