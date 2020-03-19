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
    PretrainedNN();
    void setImagePaths(vector<string> imagePaths);
    void setPlatforms(vector<pair<string, int> > platforms);
    vector<Result> classify();
    void setNerualNet(string nn);
    void threading(OpenVinoEnv *env);
private:
    vector<string> allImages;
    vector<pair<string, int> > distribution;
    string currentNN;
    vector<Result> results;
    vector<OpenVinoEnv*> envs;

};

#endif // PRETRAINEDNN_H
