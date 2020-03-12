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

class PaddingLayerCont{
public:
    int batchSize;
    int inputMaps;
    int inputHeight;
    int inputWidth;
    int outputHeight;
    int outputWidth;
    int paddingHeight;
    int paddingWidth;
    float*inputValues;
    float*outputErrors;

    ~PaddingLayerCont(){
        delete[] inputValues;
        delete[] outputErrors;
    }
};

class TestPadding{
public:
    Util* util=new Util();

    void createRandomPaddingLayerCont(PaddingLayerCont* paddingLayerCont);

    int testFeedForward();
    int testErrorComp();
};
