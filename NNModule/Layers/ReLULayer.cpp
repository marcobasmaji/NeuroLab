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
    OpenCLLayer* cLrelu = clCreator->createReluLayer(clEnv,10,inputDepth,inputHeight,inputWidth);
    this->clLayer= cLrelu;

                }

void ReLULayer::forwardPass(float input[], float output[])
{
    clLayer->computeForward(clEnv,10,inputDepth);

}

void ReLULayer::backPropagate(float upstreamGrad[])
{


}

OpenCLLayer* ReLULayer::getCLLayer()
{
    return clLayer;
}

Shape ReLULayer::getInputGrad()
{
    return InputGrad;
}
