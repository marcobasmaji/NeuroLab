#include "Tests/TestsExample/TestExample.hpp"

TEST(t1, t2)
{
    EXPECT_EQ(0, 0);
    ASSERT_THAT(0, Eq(0));
}

