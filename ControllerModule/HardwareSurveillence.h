#ifndef HARDWARESURVEILLENCE_H
#define HARDWARESURVEILLENCE_H
#include <string.h>
#include <vector>
#include <Tools/openvino/include/inference_engine.hpp>
#include "Tools/opencl/include/cl.h"


using namespace std;

class HardwareSurveillence{
public:
    HardwareSurveillence();
    vector<string> checkAvailableHardware();
private:
    InferenceEngine::Core core;
    vector<string> checkWithOpenVino();
    bool checkWithOpenCL();
};


#endif // HARDWARESURVEILLENCE_H
