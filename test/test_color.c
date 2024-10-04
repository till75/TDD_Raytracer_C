#ifdef TEST

#include "unity.h"

#include "color.h"
#include "vecmath.h"



void setUp(void)
{
}

void tearDown(void)
{
}

void test_color_Create(void)
{
    Color c;
    color_Create(&c, -0.5, 0.4, 1.7);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, -0.5, c.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.4, c.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.7, c.blue);
}

void test_color_AddColors(void)
{
    Color c1, c2;
    color_Create(&c1, 0.9, 0.6, 0.75);
//    printf("c1.blue=%f\n", c1.blue);
    color_Create(&c2, 0.7, 0.1, 0.25);
    color_AddColors(&c1, &c2);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.6, c1.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.7, c1.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 1.0, c1.blue);
}

void test_color_SubtractColors(void)
{
    Color c1, c2;
    color_Create(&c1, 0.9, 0.6, 0.75);
    color_Create(&c2, 0.7, 0.1, 0.25);
    color_SubtractColors(&c1, &c2);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.2, c1.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.5, c1.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.5, c1.blue);
}

void test_color_MultiplyColors(void)
{
    Color c1, c2;
    color_Create(&c1, 1, 0.2, 0.4);
    color_Create(&c2, 0.9, 1, 0.1);
    color_MultiplyColors(&c1, &c2);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.9, c1.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.2, c1.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.04, c1.blue);
}

void test_color_ScaleColors(void)
{
    Color c1;
    float scalar = 2.0;
    color_Create(&c1, 0.2, 0.3, 0.4);
    color_ScaleColor(&c1, scalar);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.4, c1.red);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.6, c1.green);
    TEST_ASSERT_FLOAT_WITHIN(EPSILON, 0.8, c1.blue);
}

void test_color_toPPM(void)
{
    char ppm[12];
    Color color;
    color_Create(&color, 1.1, 0.5, -3);
    color_toPPM(&color, ppm);
    
    TEST_ASSERT_EQUAL_STRING("255 128 0", ppm);
}
#endif // TEST
