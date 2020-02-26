#include "TestStarter.hpp"

//include here all the test files, don't change any other lines
#include "Tests/TestsOpenCL/TestExample.hpp"



#include <gtest/gtest.h>

TestStarter::TestStarter(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
}

int TestStarter::runAllTests(){
    return RUN_ALL_TESTS();
}
