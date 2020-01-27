#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class MaxPoolingLayer : public Layer
{
public:
    MaxPoolingLayer(OpenCLEnvironment* clEnv,
                    size_t inputHeight,
                    size_t inputWidth,
                    size_t inputDepth,
                    size_t poolingWindowHeight,
                    size_t poolingWindowWidth,
                    size_t verticalStride,
                    size_t horizontalStride);
    void forwardPass(float input[], float output[]);
    void backPropagate(float upstreamGrad[]);


    OpenCLLayer* getCLLayer();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    size_t poolingWindowHeight;
    size_t poolingWindowWidth;
    size_t verticalStride;
    size_t horizontalStride;

    Shape input;
    Shape output;

    Shape gradientWrtInput;

};

#endif // MAXPOOLINGLAYER_H
