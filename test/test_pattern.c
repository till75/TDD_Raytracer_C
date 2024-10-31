
#ifdef TEST

#include "unity.h"

#include "pattern.h"
#include "color.h"
#include "vecmath.h"
#include "ray.h"
#include <stdio.h>

static Color black = {0,0,0};
static Color white = {1,1,1};

void setUp(void)
{
}

void tearDown(void)
{
}

void test_pattern_StripePatternCreate(void)
{
    Pattern sp;
    pattern_CreateStripePattern(&sp, &black, &white);

    TEST_ASSERT_TRUE(color_AreEqualColors(&black, &(sp.c1)));
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &(sp.c2)));
}

void test_pattern_StripePatternIsConstantInY(void)
{
    Pattern sp;
    pattern_CreateStripePattern(&sp, &white, &black);
    Tuple4d pt1 = {0,0,0,1};
    Tuple4d pt2 = {0,1,0,1};
    Tuple4d pt3 = {0,2,0,1};
    Color c;

    pattern_StripeAt(&sp, &pt1, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    pattern_StripeAt(&sp, &pt2, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    pattern_StripeAt(&sp, &pt3, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));
}

void test_pattern_StripePatternIsConstantInZ(void)
{
    Pattern sp;
    pattern_CreateStripePattern(&sp, &white, &black);
    Tuple4d pt1 = {0,0,0,1};
    Tuple4d pt2 = {0,0,1,1};
    Tuple4d pt3 = {0,0,2,1};
    Color c;

    pattern_StripeAt(&sp, &pt1, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    pattern_StripeAt(&sp, &pt2, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    pattern_StripeAt(&sp, &pt3, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));
}

void test_pattern_StripePatternAlternatesInX(void)
{
    Pattern sp;
    pattern_CreateStripePattern(&sp, &white, &black);
    Color c;

    Tuple4d pt1 = {0,0,0,1};
    pattern_StripeAt(&sp, &pt1, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    Tuple4d pt2 = {0.9,0,0,1};
    pattern_StripeAt(&sp, &pt2, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));

    Tuple4d pt3 = {1,0,0,1};
    pattern_StripeAt(&sp, &pt3, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&black, &c));

    Tuple4d pt4 = {-0.1,0,0,1};
    pattern_StripeAt(&sp, &pt4, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&black, &c));

    Tuple4d pt5 = {-1.0,0,0,1};
    pattern_StripeAt(&sp, &pt5, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&black, &c));

    Tuple4d pt6 = {-1.1,0,0,1};
    pattern_StripeAt(&sp, &pt6, &c);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &c));
}

void test_pattern_LightingWithStripePattern(void)
{
    Pattern sp;
    pattern_CreateStripePattern(&sp, &white, &black);
    Material mat = {{0,0,0}, 1,0,0,0, {STRIPES, {1,1,1},{0,0,0}}};
    Tuple4d eyev = {0,0,-1,0};
    Tuple4d normalv = {0,0,1};
    PointLight light = {{0,0,-10,1},{1,1,1}};

    Color res;

    Tuple4d pt1 = {0.9, 0, 0, 1};
    ray_Lighting(&res, &mat, &light, &pt1, &eyev, &normalv, false);
    TEST_ASSERT_TRUE(color_AreEqualColors(&white, &res));

    Tuple4d pt2 = {1.1, 0, 0, 1};
    ray_Lighting(&res, &mat, &light, &pt2, &eyev, &normalv, false);
    TEST_ASSERT_TRUE(color_AreEqualColors(&black, &res));
}

#endif // TEST
