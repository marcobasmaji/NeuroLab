#include "Tests/TestsExample/TestExample.hpp"

TEST(TestExample, Test1)
{
    EXPECT_EQ(0, 0);
    ASSERT_THAT(0, Eq(0));
}
