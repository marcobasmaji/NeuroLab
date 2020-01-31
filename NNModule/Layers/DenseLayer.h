#ifndef DENSELAYER_H
#define DENSELAYER_H

#include <iostream>
#include <DataModule/Shape.h>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLLayer.hpp>
#include <HardwareModule/OpenCL/OpenCLLayerCreator.hpp>
#include "Layer.h"

class DenseLayer : public Layer
{
public:
    DenseLayer(OpenCLEnvironment* clEnv,
               size_t inputHeight,
               size_t inputWidth,
               size_t inputDepth,
               size_t numOutputs);
    void forwardPass(float input[], float output[]);
    void backPropagate(float upstreamGrad[]);
    Shape getGradientWrtWeights() { return gradWeights; }

    Shape getGradientWrtInput() { return gradInput; }

    Shape getGradientWrtBiases() { return gradBiases; }

    Shape getWeights() { return weights; }

    Shape getBiases() { return biases; }

    void setWeights(Shape weights) { this->weights = weights; }

    void setBiases(Shape biases) { this->biases = biases; }


    OpenCLLayer *getCLLayer();
    void updateWeights();

private:
    OpenCLEnvironment* clEnv;
    OpenCLLayer* clLayer;
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
    float* getWeights(int length);
    float getRandom();
};

#endif // DENSELAYER_H
