#ifndef RELULAYER_H
#define RELULAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"


class ReLULayer: public Layer
{
public:
    ReLULayer(size_t inputHeight,
           size_t inputWidth,
           size_t inputDepth);
    //Forward and Back Propagation
    void forwardPass(Shape &input, Shape &output);
    void backPropagate(Shape upstreamGrad);
    //Getter for the Input Gradient
    Shape getInputGrad();

private:
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    Shape input;
    Shape output;

    Shape InputGrad;
};

#endif // RELULAYER_H
