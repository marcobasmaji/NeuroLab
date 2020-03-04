#ifndef UTIL_HPP
#define UTIL_HPP

#define RANDOM_SEED 12345;
#include "HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironment.hpp"
#include "HardwareModule/OpenCL/HardwareType.cpp"

class Util
{
public:
    Util();
    void createRandomValues(float* array, int length);
    int getRandomIntValue(int fromValue, int toValue);
};

#endif // UTIL_HPP
