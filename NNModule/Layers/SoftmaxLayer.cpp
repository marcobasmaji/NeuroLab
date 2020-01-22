#include "SoftmaxLayer.h"

SoftmaxLayer::SoftmaxLayer(size_t numInputs) : numInputs(numInputs)
{

}

void SoftmaxLayer::forwardPass(Shape &input, Shape &output)
{

}
void SoftmaxLayer::backPropagate(Shape upstreamGrad)
{

}
Shape SoftmaxLayer::getInputGrad()
{
    return inputGrad;
}
