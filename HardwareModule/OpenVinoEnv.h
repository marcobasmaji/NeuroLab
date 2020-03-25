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
    void classify();
    void chooseNeuralNet(string nn);
    void setImageNames(std::vector<std::string> imageNamesAttribute);
    void setDevice(string device);
    vector<Result> getResults();

    void setCore(InferenceEngine::Core core);
    vector<Result> processOutput();
private:
    void readIR();
    void configureInputAndOutput();
    void createRequestsWithInput();
    void infer();

    InferenceEngine::Core core;
    InferenceEngine::CNNNetwork cnnnetworkAttribute;
    InferenceEngine::InputsDataMap inputInfoAttribute;
    InferenceEngine::OutputsDataMap outputInfoAttribute;
    string structurePath;
    string weightsPath;
    std::vector<std::string> imageNamesAttribute;
    vector<Result> endResultsAttribute;
    string deviceName;
    std::vector<std::shared_ptr<unsigned char>> imagesDataAttribute;
    std::vector<std::string> validImageNamesAttribute;
    size_t batchSizeAttribute;
    InferenceEngine::InferRequest inferRequestAttribute;
    vector<pair<string, int> > distributionAttribute;
};

#endif // OPENVINOENV_H
