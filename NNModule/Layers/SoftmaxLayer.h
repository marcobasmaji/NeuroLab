#ifndef SOFTMAXLAYER_H
#define SOFTMAXLAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"

class SoftmaxLayer : public Layer
{
public:
    SoftmaxLayer(size_t numInputs);
    void forwardPass(Shape &input, Shape &output);
    void backPropagate(Shape upstreamGrad);
    Shape getInputGrad();
private:
    size_t numInputs;
    Shape input;
    Shape output;

    Shape inputGrad;
};

#endif // SOFTMAXLAYER_H
