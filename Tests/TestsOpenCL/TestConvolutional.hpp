#pragma once

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "Tests/TestsOpenCL/Util.hpp"
#include "Tools/opennn/files/opennn.h"
#include "HardwareModule/OpenCL/OpenCLLayer.hpp"
#include "HardwareModule/OpenCL/OpenCLLayerCreator.hpp"
#include "HardwareModule/OpenCL/HardwareEnvironment.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp"
#include "HardwareModule/OpenCL/HardwareType.cpp"

using namespace testing;
using namespace OpenNN;

class ConvLayerCont{
public:
    int batchSize;
    int inputMaps;
    int inputHeight;
    int outputMaps;
    int outputHeight;
    int kernelHeight;
    int strideHeight;
    int inputWidth;
    int outputWidth;
    int kernelWidth;
    int strideWidth;
    float*inputValues;
    float*outputErrors;
    float*weights;
    float*biases;
    float learningRate;

    ~ConvLayerCont(){
        delete[] inputValues;
        delete[] outputErrors;
        delete[] biases;
        delete[] weights;
    }
};

class TestConvolutional{
public:
    Util* util=new Util();

    void parseStructure(ConvLayerCont* convLayerCont, string content);

    void createRandomConvLayerCont(ConvLayerCont* convLayer);
    void createConvLayerOpennn(ConvLayerCont* convLayerCont, ConvolutionalLayer* convLayerOpennn);

    int testFeedForward();
    int testErrorComp();
    int testWeightsUpdate();
};
