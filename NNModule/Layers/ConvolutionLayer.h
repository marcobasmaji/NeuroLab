#ifndef COVOLUTIONLAYER_H
#define COVOLUTIONLAYER_H
#include <iostream>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class ConvolutionLayer: public Layer
{
public:
    ConvolutionLayer(OpenCLEnvironment* clEnv,
                     size_t inputHeight,
                     size_t inputWidth,
                     size_t inputDepth,
                     size_t filterHeight,
                     size_t filterWidth,
                     size_t horizontalStride,
                     size_t verticalStride,
                     size_t numFilters);
    void forwardPass();
    void backPropagate();
    OpenCLLayer* getCLLayer();
    void updateWeights();


private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    size_t filterHeight;
    size_t filterWidth;
    size_t horizontalStride;
    size_t verticalStride;
    size_t numFilters;

    float* getWeights(int length);
    float getRandom();
};

#endif // COVOLUTIONLAYER_H
