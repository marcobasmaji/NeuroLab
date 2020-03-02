#ifndef DENSELAYER_H
#define DENSELAYER_H

#include <iostream>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class DenseLayer : public Layer
{
public:
    DenseLayer(OpenCLEnvironment* clEnv,
               size_t inputHeight,
               size_t inputWidth,
               size_t inputDepth,
               size_t numOutputs);
    void forwardPass();
    void backPropagate();
    OpenCLLayer *getCLLayer();
    void updateWeights();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    size_t numOutputs;
    float* getWeights(int length);
    float getRandom();
};

#endif // DENSELAYER_H
