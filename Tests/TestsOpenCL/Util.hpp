#ifndef UTIL_HPP
#define UTIL_HPP

#define RANDOM_SEED 12345;
#include "HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironment.hpp"
#include "HardwareModule/OpenCL/HardwareType.cpp"

#include <string>
#include <vector>

using namespace std;

class Util
{
public:
    Util();
    void createRandomValues(float* array, int length);
    int getRandomIntValue(int fromValue, int toValue);
    void loadStringToArray(string dir, vector<float>*data);
    void convertVectorToFloatArray(vector<float>*vectorData, float*array);
    string loadFile(string dir);
};

#endif // UTIL_HPP
