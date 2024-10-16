
#ifdef TEST

#include "unity.h"
#include <string.h>
#include "world.h"

void setUp(void)
{
}

void tearDown(void)
{
}

void test_world_EmptyOnCreation(void)
{
    World w;
    world_Create(&w);

    TEST_ASSERT_TRUE(world_getNumberOfObjects(&w) == 0);
    TEST_ASSERT_TRUE(w.lightSource == NULL);
}

void test_world_CreateDefault(void)
{
    World w;
    world_CreateDefault(&w);


}

#endif // TEST
