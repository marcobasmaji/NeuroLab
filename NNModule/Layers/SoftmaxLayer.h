#ifndef SOFTMAXLAYER_H
#define SOFTMAXLAYER_H
#include <iostream>
#include <DataModule/Shape.h>
class SoftmaxLayer
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
