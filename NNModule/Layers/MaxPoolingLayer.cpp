#include "MaxPoolingLayer.h"

MaxPoolingLayer::MaxPoolingLayer(OpenCLEnvironment* clEnv,
                                 size_t inputHeight,
                                 size_t inputWidth,
                                 size_t inputDepth,
                                 size_t poolingWindowHeight,
                                 size_t poolingWindowWidth,
                                 size_t verticalStride,
                                 size_t horizontalStride)
{
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* clMax = openCLLayerCreator->createMaxPoolLayer(clEnv,10,inputDepth,inputHeight,
                                                                inputWidth,14,14,poolingWindowHeight,
                                                                poolingWindowWidth,horizontalStride,verticalStride);
    this->clLayer = clMax;

}

void MaxPoolingLayer::forwardPass(float input[],float output[])
{
    clLayer->computeForward(clEnv,10,inputDepth);
}

void MaxPoolingLayer::backPropagate(float upstreamGrad[])
{
    clLayer->computeErrorComp(clEnv,16);
}

OpenCLLayer *MaxPoolingLayer::getCLLayer()
{
    return clLayer;
}
