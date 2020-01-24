#include "ReLULayer.h"
#include "../../HardwareModule/OpenCL/OpenCLLayerCreator.hpp"
#include "../../HardwareModule/OpenCL/OpenCLLayer.hpp"

ReLULayer::ReLULayer(size_t inputHeight,
                     size_t inputWidth,
                     size_t inputDepth) :
                    inputHeight(inputHeight),
                    inputWidth(inputWidth),
                    inputDepth(inputDepth)
                {
    OpenCLLayerCreator* clCreator = new OpenCLLayerCreator();
    //OpenCLLayer* relu = clCreator->createReluLayer(clEnv,);

                }

void ReLULayer::forwardPass(Shape &input, Shape &output)
{

}

void ReLULayer::backPropagate(Shape upstreamGrad)
{

}

Shape ReLULayer::getInputGrad()
{
    return InputGrad;
}
