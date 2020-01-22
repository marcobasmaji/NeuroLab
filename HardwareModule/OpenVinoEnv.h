#ifndef OPENVINOENV_H
#define OPENVINOENV_H
#include <inference_engine.hpp>
#include <Tools/common/format_reader/format_reader_ptr.h>
#include <iostream>
#include <DataModule/Result.h>

using namespace std;
using namespace InferenceEngine;


class OpenVinoEnv
{
public:
    OpenVinoEnv();
    vector<Result> classify();
    void chooseNeuralNet(string nn);
    void setImageNames(std::vector<std::string> imageNames);

private:
    void readIR();
    void configureInputAndOutput();
    void loadModel();
    void createInferRequest();
    void prepareInput();
    void infer();
    void processOutput();
    // for hardware Distrubution
    void setPlatforms(vector<string>);

    InferenceEngine::Core core;
    InferenceEngine::InferencePlugin plugin;
    InferenceEngine::CNNNetwork cnnnetwork;
    InferenceEngine::InputsDataMap inputInfo;
    InferenceEngine::OutputsDataMap outputInfo;


    //string pathToIR;
    string structurePath;
    string weightsPath;
    std::vector<std::string> imageNames;
    vector<Result> endResults;
    string deviceName;
};

#endif // OPENVINOENV_H
