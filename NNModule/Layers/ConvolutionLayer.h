#ifndef COVOLUTIONLAYER_H
#define COVOLUTIONLAYER_H
#include <iostream>
#include <DataModule/Shape.h>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class CovolutionLayer: public Layer
{
public:
    CovolutionLayer(OpenCLEnvironment* clEnv,
            size_t inputHeight,
            size_t inputWidth,
            size_t inputDepth,
            size_t filterHeight,
            size_t filterWidth,
            size_t horizontalStride,
            size_t verticalStride,
            size_t numFilters);
    void forwardPass(float input[105][105][3]);
    void backPropagate(Shape upstreamGrad);
private:
    OpenCLEnvironment* clEnv;
    size_t inputHeight;
      size_t inputWidth;
      size_t inputDepth;
      size_t filterHeight;
      size_t filterWidth;
      size_t horizontalStride;
      size_t verticalStride;
      size_t numFilters;

      Shape filters;
      Shape input;
        Shape output;
        Shape gradInput;
        Shape accumulatedGradInput;
        Shape gradFilters;
        Shape accumulatedGradFilters;
};

#endif // COVOLUTIONLAYER_H
