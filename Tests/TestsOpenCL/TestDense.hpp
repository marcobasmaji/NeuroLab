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

class DenseLayerCont{
public:
    int inputMaps;
    int inputHeight;
    int inputWidth;
    int outputNeurons;
    int batchSize;
    float* biases;
    float* weights;
    float*inputValues;
    float*outputErrors;
    float learningRate;

    ~DenseLayerCont(){
        delete[]biases;
        delete[]weights;
        delete[]inputValues;
        delete[]outputErrors;
    }
};

class TestDense{
public:
    Util* util=new Util();

    void parseStructure(DenseLayerCont* denseLayerCont,string content);

    void createRandomDenseLayerCont(DenseLayerCont* denseLayerCont);
    void createPerzeptronLayerOpennn(DenseLayerCont* denseLayerCont, PerceptronLayer* perceptronLayerOpennn);

    int testFeedForward();
    int testErrorComp();
    int testWeightsUpdate();
};
