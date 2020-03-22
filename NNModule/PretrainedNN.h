#ifndef PRETRAINEDNN_H
#define PRETRAINEDNN_H
#include <iostream>
#include <list>
#include <vector>
#include <thread>

#include <HardwareModule/OpenVinoEnv.h>
#include <DataModule/Result.h>

using namespace std;

class PretrainedNN
{
public:
    InferenceEngine::Core* core;
    PretrainedNN();
    void setImagePaths(vector<string> imagePaths);
    void setPlatforms(vector<pair<string, int> > platforms);
    void classify();
    void setNerualNet(string nn);
    void threading(OpenVinoEnv *env);
    vector<Result> getResults();
private:
    vector<string> allImages;
    vector<pair<string, int> > distribution;
    string currentNN;
    vector<Result> results;
    vector<OpenVinoEnv*> envs;

};

#endif // PRETRAINEDNN_H
