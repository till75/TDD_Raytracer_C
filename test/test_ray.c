#ifdef TEST

#include "unity.h"

#include "ray.h"
#include "vecmath.h"
#include "transforms.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_ray_CreateAndQuery(void)
{
    Tuple4d origin = {1,2,3,1};
    Tuple4d direction = {4,5,6,0};
    Ray r;
    ray_Create(&r, &origin, &direction);

    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(r.origin), &origin));
    TEST_ASSERT_TRUE(vecmath_AreEqualTuples4d(&(r.direction), &direction));
}

#endif // TEST
