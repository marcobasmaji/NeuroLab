#ifndef RELULAYER_H
#define RELULAYER_H

#include <iostream>
#include <DataModule/Shape.h>
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
    void forwardPass(float input[], float output[]);
    void backPropagate(float upstreamGrad[]);
    OpenCLLayer* getCLLayer();
    //Getter for the Input Gradient
    Shape getInputGrad();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    Shape input;
    Shape output;

    Shape InputGrad;
};

#endif // RELULAYER_H
