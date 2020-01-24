#ifndef MAXPOOLINGLAYER_H
#define MAXPOOLINGLAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"


class MaxPoolingLayer : public Layer
{
public:
    MaxPoolingLayer(size_t inputHeight,
                      size_t inputWidth,
                      size_t inputDepth,
                      size_t poolingWindowHeight,
                      size_t poolingWindowWidth,
                      size_t verticalStride,
                      size_t horizontalStride);
    void forwardPass(Shape &input, Shape &output);
    void backPropagate(Shape &upstreamGrad);

private:
    size_t inputHeight;
    size_t inputWidth;
    size_t inputDepth;
    size_t poolingWindowHeight;
    size_t poolingWindowWidth;
    size_t verticalStride;
    size_t horizontalStride;

    Shape input;
    Shape output;

    Shape gradientWrtInput;

};

#endif // MAXPOOLINGLAYER_H
