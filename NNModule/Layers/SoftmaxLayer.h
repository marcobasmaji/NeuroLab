#ifndef SOFTMAXLAYER_H
#define SOFTMAXLAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class SoftmaxLayer : public Layer
{
public:
    SoftmaxLayer(OpenCLEnvironment* clEnv,
size_t numInputs);
    void forwardPass(float input[], float output[]);
    void backPropagate(float upstreamGrad[]);
    Shape getInputGrad();
    OpenCLLayer *getCLLayer();
    float* getLayerOutput();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t numInputs;
    Shape input;
    //Shape output;

    Shape inputGrad;

};

#endif // SOFTMAXLAYER_H
