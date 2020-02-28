#include "ReLULayer.h"
#include "../../HardwareModule/OpenCL/OpenCLLayerCreator.hpp"
#include "../../HardwareModule/OpenCL/OpenCLLayer.hpp"

ReLULayer::ReLULayer(OpenCLEnvironment* clEnv,
                     size_t inputHeight,
                     size_t inputWidth,
                     size_t inputDepth) :
                    inputHeight(inputHeight),
                    inputWidth(inputWidth),
                    inputDepth(inputDepth)
                {
    this->clEnv = clEnv;
    OpenCLLayerCreator* clCreator = new OpenCLLayerCreator();
    OpenCLLayer* cLrelu = clCreator->createReluLayer(clEnv,16,inputDepth,inputHeight,inputWidth);
    this->clLayer= cLrelu;

                }

void ReLULayer::forwardPass()
{
    clLayer->computeForward(clEnv,16,inputDepth);

}

void ReLULayer::backPropagate()
{
    clLayer->computeErrorComp(clEnv,16);
}

OpenCLLayer* ReLULayer::getCLLayer()
{
    return clLayer;
}
