#include "Util.hpp"
#include <stdlib.h>
#include <time.h>
#include "HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironment.hpp"

Util::Util()
{
    unsigned int randomSeed=RANDOM_SEED;
    srand(randomSeed);
}

void Util::createRandomValues(float* array, int length){
    for(int i=0;i<length;i++){
        float value=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float b=static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        value*=(b<0.5 ? 1 : -1);
        array[i]=value;
    }
}
int Util::getRandomIntValue(int fromValue, int toValue){
    int values=toValue-fromValue+1;
    return rand()%values+fromValue;
}
