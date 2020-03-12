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

class SoftmaxLayerCont{
public:
    int neurons;
    int batchSize;
    float*inputValues;
    float*outputErrors;

    ~SoftmaxLayerCont(){
        delete[]inputValues;
        delete[]outputErrors;
    }
};

class TestSoftmax{
public:
    Util* util=new Util();

    void createRandomSoftmaxLayerCont(SoftmaxLayerCont* softmaxLayerCont);
    void createProbabilisticLayerOpennn(SoftmaxLayerCont* softmaxLayerCont, ProbabilisticLayer* probabilisticLayerOpennn);

    int testFeedForward();
    int testErrorComp();
};
