#include "SoftmaxLayer.h"

SoftmaxLayer::SoftmaxLayer(OpenCLEnvironment* clEnv,
                           size_t numInputs) : numInputs(numInputs)
{
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* cLconv = openCLLayerCreator->createSoftmaxLayer(clEnv,1,numInputs,1,1);
    this->clLayer = cLconv;
}

void SoftmaxLayer::forwardPass()
{
     clLayer->computeForward(clEnv,1,numInputs);
}
void SoftmaxLayer::backPropagate()
{
    clLayer->computeErrorComp(clEnv,1);
}

OpenCLLayer *SoftmaxLayer::getCLLayer()
{
    return clLayer;
}
float* SoftmaxLayer::getLayerOutput()
{
    return clLayer->getOutputs(clEnv,1,numInputs,1,1,NULL);
}
