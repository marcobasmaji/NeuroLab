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

class PoolingLayerCont{
public:
    int batchSize;
    int inputMaps;
    int inputHeight;
    int outputHeight;
    int poolingHeight;
    int strideHeight;
    int inputWidth;
    int outputWidth;
    int poolingWidth;
    int strideWidth;
    float*inputValues;
    float*outputErrors;

    ~PoolingLayerCont(){
        delete[] inputValues;
        delete[] outputErrors;
    }
};

class TestMaxPooling{
public:
    Util* util=new Util();

    void createRandomPoolingLayerCont(PoolingLayerCont* poolingLayer);
    void createPoolingLayerOpennn(PoolingLayerCont* poolingLayerCont, PoolingLayer* poolingLayerOpennn);

    int testFeedForward();
    int testErrorComp();
};
