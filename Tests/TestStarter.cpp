//don't change this file

#include "TestStarter.hpp"
#include <gtest/gtest.h>

TestStarter::TestStarter(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
}

int TestStarter::runAllTests(){
    return RUN_ALL_TESTS();
}
