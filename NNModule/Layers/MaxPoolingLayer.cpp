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
    size_t outputMaps = (inputHeight-poolingWindowHeight)/horizontalStride +1;
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* clMax = openCLLayerCreator->createMaxPoolLayer(clEnv,1,inputDepth,inputHeight,
                                                                inputWidth,outputMaps,outputMaps,poolingWindowHeight,
                                                                poolingWindowWidth,horizontalStride,verticalStride);
    this->clLayer = clMax;

}

void MaxPoolingLayer::forwardPass()
{
    clLayer->computeForward(clEnv,1,inputDepth);
}

void MaxPoolingLayer::backPropagate()
{
    clLayer->computeErrorComp(clEnv,1);
}

OpenCLLayer *MaxPoolingLayer::getCLLayer()
{
    return clLayer;
}
