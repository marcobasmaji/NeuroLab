#include "SoftmaxLayer.h"

SoftmaxLayer::SoftmaxLayer(OpenCLEnvironment* clEnv,
                           size_t numInputs) : numInputs(numInputs)
{
    this->clEnv = clEnv;
    OpenCLLayerCreator* openCLLayerCreator = new OpenCLLayerCreator();
    OpenCLLayer* cLconv = openCLLayerCreator->createSoftmaxLayer(clEnv,16,numInputs,1,1);
    this->clLayer = cLconv;
}

void SoftmaxLayer::forwardPass(float input[],float output[])
{
     clLayer->computeForward(clEnv,16,numInputs);
}
void SoftmaxLayer::backPropagate(float upstreamGrad[])
{
    // upstream ist ergebnis von Loss
    //clLayer->setOutputErrors(clEnv,upstreamGrad,numInputs);
    clLayer->computeErrorComp(clEnv,10);
}
Shape SoftmaxLayer::getInputGrad()
{
    return inputGrad;
}

OpenCLLayer *SoftmaxLayer::getCLLayer()
{
    return clLayer;
}
float* SoftmaxLayer::getLayerOutput()
{
    return clLayer->getOutputs(clEnv,16,numInputs,1,1,nullptr);
}
