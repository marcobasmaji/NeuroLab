#ifndef OPENVINOENV_H
#define OPENVINOENV_H
#include <inference_engine.hpp>
using namespace InferenceEngine;

class OpenVinoEnv
{
public:
    OpenVinoEnv();
    void initMovidius();
    void classify();

private:
    InferenceEngine::Core core;
    InferenceEngine::InferencePlugin plugin;
    InferenceEngine::CNNNetwork cnnnetwork;
    InferenceEngine::InputsDataMap inputInfo;
    InferenceEngine::OutputsDataMap outputInfo;
    //string pathToIR;

};

#endif // OPENVINOENV_H
