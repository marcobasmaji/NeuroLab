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
    vector<pair<string,int>> getDistribution();

private:
    void readIR();
    void configureInputAndOutput();
    void CreateRequestsWithInput();
    void infer();
    vector<Result> processOutput();

    InferenceEngine::Core core;
    InferenceEngine::CNNNetwork cnnnetwork;
    InferenceEngine::InputsDataMap inputInfo;
    InferenceEngine::OutputsDataMap outputInfo;
    string structurePath;
    string weightsPath;
    std::vector<std::string> imageNames;
    vector<Result> endResults;
    string deviceName;
    std::vector<std::shared_ptr<unsigned char>> imagesData;
    std::vector<std::string> validImageNames;
    size_t batchSize;
    vector<InferenceEngine::InferRequest> requests;
    vector<pair<string, int> > distribution;
};

#endif // OPENVINOENV_H
