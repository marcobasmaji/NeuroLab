#ifndef OPENVINOENV_H
#define OPENVINOENV_H
#include <inference_engine.hpp>
#include <Tools/common/format_reader/format_reader_ptr.h>
#include <iostream>
#include <DataModule/Result.h>
#include<chrono>
#include <condition_variable>

using namespace std;
using namespace std::chrono;


class OpenVinoEnv
{
public:
    OpenVinoEnv();
    vector<Result> classify();
    void chooseNeuralNet(string nn);
    void setImageNames(std::vector<std::string> imageNames);
    void setDistribution(vector<pair<string, int> >);

private:
    void readIR();
    void configureInputAndOutput();


    void loadModel();
    void createInferRequest();
    void prepareInput();
    void infer();
    vector<Result> processOutput();
    // for hardware Distrubution


    InferenceEngine::Core core;
    InferenceEngine::InferencePlugin plugin;
    InferenceEngine::CNNNetwork cnnnetwork;
    InferenceEngine::InputsDataMap inputInfo;
    InferenceEngine::OutputsDataMap outputInfo;
    InferenceEngine::ExecutableNetwork execNetwork;
    InferenceEngine::InferRequest inferRequest;


    //string pathToIR;
    string structurePath;
    string weightsPath;
    std::vector<std::string> imageNames;
    vector<Result> endResults;
    string deviceName;
    std::vector<std::shared_ptr<unsigned char>> imagesData;
    std::vector<std::string> validImageNames;
    size_t batchSize;
    vector<InferenceEngine::ExecutableNetwork> execNetworks;
    vector<string> devices;
    vector<InferenceEngine::InferRequest> requests;
    vector<pair<string, int> > distribution;
};

#endif // OPENVINOENV_H
