#ifdef TEST
#include "unity.h"
#include "canvas.h"
#include "color.h"
#include "vecmath.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_canvas_Create(void)
{
    Canvas c;
    Color color;
    int dim_x = 10;
    int dim_y = 20;
    canvas_Create(&c, dim_x, dim_y);
    TEST_ASSERT_EQUAL(dim_x, c.width);
    TEST_ASSERT_EQUAL(dim_y, c.height);
 
    for (int y = 0; y<dim_y; y++) 
    {
        for (int x = 0; x<dim_x; x++)
        {
//            printf("Asking for color of (%d/%d)\n", x, y);
            color = *(canvas_GetColor(&c, x, y));
//            printf("Color is (%f/%f/%f)\n", color.red, color.green, color.blue);
            TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, color.red);
            TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, color.green);
            TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, color.blue);
        }
    }
    canvas_Destroy(&c);
}

void test_canvas_DrawPixel(void)
{
    Canvas canvas;
    Color color_write, color_read;
    color_Create(&color_write, 1, 0, 0);
    int dim_x = 10;
    int dim_y = 20;
    canvas_Create(&canvas, dim_x, dim_y);

    canvas_DrawPixel(&canvas, &color_write, 2, 3);
    color_read = *(canvas_GetColor(&canvas, 2, 3));

//    printf("Color is (%f/%f/%f)\n", color_read.red, color_read.green, color_read.blue);

    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, color_read.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, color_read.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.0, color_read.blue);

    canvas_Destroy(&canvas);
}

void test_canvas_HeaderToPPM(void)
{
    Canvas canvas;
    int dim_x = 10;
    int dim_y = 20;
    canvas_Create(&canvas, dim_x, dim_y);

    char header[20];
    canvas_HeaderToPPM(&canvas, header);
//    printf("Header is\n%s", header);

    TEST_ASSERT_EQUAL_STRING("P3\n10 20\n255\n", header);

    canvas_Destroy(&canvas);
}

void test_canvas_PixelRowToPPM(void)
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

    char pixelRowPPM[dim_x * 3 * 4];
    pixelRowPPM[0] = '\0';
    canvas_PixelRowToPPM(&canvas, pixelRowPPM, 0);
//    printf("Pixel data in row 0 is\n%s", pixelRowPPM);

    TEST_ASSERT_EQUAL_STRING("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0", pixelRowPPM);
    canvas_Destroy(&canvas);
}


void test_canvas_PixelDataToPPM(void)
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
    char pixelPPM[dim_x * dim_y * 3 * 4]; 
    pixelPPM[0] = '\0';
    canvas_PixelsToPPM(&canvas, pixelPPM);
//    printf("Pixel data is\n%s", pixelPPM);

    TEST_ASSERT_EQUAL_STRING("255 0 0 0 0 0 0 0 0 0 0 0 0 0 0\n"
                             "0 0 0 0 0 0 0 128 0 0 0 0 0 0 0\n"
                             "0 0 0 0 0 0 0 0 0 0 0 0 0 0 255\n"
                             , pixelPPM);
    canvas_Destroy(&canvas);
}

#endif // TEST
