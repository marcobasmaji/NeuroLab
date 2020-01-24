#ifndef DENSELAYER_H
#define DENSELAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"

class DenseLayer : public Layer
{
public:
    DenseLayer(size_t inputHeight,
                 size_t inputWidth,
                 size_t inputDepth,
                 size_t numOutputs);
    void forwardPass(Shape &input, Shape &output);
    void backPropagate(Shape &upstreamGrad);
    void updateWeightsAndBiases(size_t batchSize, double learningRate);
    Shape getGradientWrtWeights() { return gradWeights; }

    Shape getGradientWrtInput() { return gradInput; }

    Shape getGradientWrtBiases() { return gradBiases; }

    Shape getWeights() { return weights; }

    Shape getBiases() { return biases; }

     void setWeights(Shape weights) { this->weights = weights; }

     void setBiases(Shape biases) { this->biases = biases; }

private:
     size_t inputHeight;
       size_t inputWidth;
       size_t inputDepth;
       Shape input;

       size_t numOutputs;
       Shape output;

       Shape weights;
       Shape biases;

       Shape gradInput;
       Shape gradWeights;
       Shape gradBiases;

       Shape accumulatedGradInput;
       Shape accumulatedGradWeights;
       Shape accumulatedGradBiases;
};

#endif // DENSELAYER_H
