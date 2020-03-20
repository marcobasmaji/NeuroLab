#include "ControllerModule/MasterController.h"
//#include "NNModule/NeuroLabNet.h"
#include <ctime>
#include <unistd.h>
#include <iostream>
using namespace std;

//#define TEST_PROJECT      //comment this line out to start the tests
//#define CREATE_WEIGHTS    //commit this line out to create random weights and biases

#ifdef TEST_PROJECT
#include "Tests/TestStarter.hpp"
#endif

#ifdef CREATE_WEIGHTS
#include "DataModule/WeightsAndBiasesCreator.h"
#endif

#include "DataModule/WeightsAndBiasesCreator.h"

int main(int argc, char *argv[]) {

    #if defined(TEST_PROJECT)
        TestStarter *testStarter=new TestStarter(argc,argv);
        return testStarter->runAllTests();
    #elif defined(CREATE_WEIGHTS)
        WeightsAndBiasesCreator creator;
        creator.createWeightsAndBiases();
    #else
        MasterController masterController;
    #endif

    return 0;
}
