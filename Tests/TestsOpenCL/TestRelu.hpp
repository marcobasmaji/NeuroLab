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

class ConvReluLayerCont{
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

    ~ConvReluLayerCont(){
        delete[] inputValues;
        delete[] outputErrors;
        delete[] biases;
        delete[] weights;
    }
};

class TestRelu{
public:
    Util* util=new Util();

    void createRandomConvReluLayerCont(ConvReluLayerCont* convReluLayer);
    void createConvReluLayerOpennn(ConvReluLayerCont* convReluLayer, ConvolutionalLayer* convReluLayerOpennn);

    int testFeedForward();
    int testErrorComp();
};
