#ifndef SOFTMAXLAYER_H
#define SOFTMAXLAYER_H

#include <iostream>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class SoftmaxLayer : public Layer
{
public:
    SoftmaxLayer(OpenCLEnvironment* clEnv,
size_t numInputs);
    void forwardPass();
    void backPropagate();
    OpenCLLayer *getCLLayer();
    float* getLayerOutput();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t numInputs;
};

#endif // SOFTMAXLAYER_H
