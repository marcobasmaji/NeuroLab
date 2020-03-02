#ifndef RELULAYER_H
#define RELULAYER_H

#include <iostream>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"


class ReLULayer: public Layer
{
public:
    ReLULayer(OpenCLEnvironment* clEnv,
              size_t inputHeight,
           size_t inputWidth,
           size_t inputDepth);
    //Forward and Back Propagation
    void forwardPass();
    void backPropagate();
    OpenCLLayer* getCLLayer();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
};

#endif // RELULAYER_H
