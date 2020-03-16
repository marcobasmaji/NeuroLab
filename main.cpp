#include "ControllerModule/MasterController.h"
//#include "NNModule/NeuroLabNet.h"
#include <ctime>
#include <unistd.h>
#include <iostream>
using namespace std;

//#define TEST_PROJECT    //comment this line out to start the tests

#ifdef TEST_PROJECT
#include "Tests/TestStarter.hpp"
#endif

int main(int argc, char *argv[]) {

    #ifdef TEST_PROJECT
        TestStarter *testStarter=new TestStarter(argc,argv);
        return testStarter->runAllTests();
    #else
        MasterController masterController;
    #endif

}


