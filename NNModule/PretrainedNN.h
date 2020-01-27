#ifndef PRETRAINEDNN_H
#define PRETRAINEDNN_H
#include <iostream>
#include <list>
#include <vector>

#include <HardwareModule/OpenVinoEnv.h>
#include <DataModule/Result.h>

using namespace std;

class PretrainedNN
{
public:
    PretrainedNN();
    void setImagePaths(vector<string> imagePaths);
    void setPlatforms(vector<string> platforms);
    vector<Result> classify();
    void setNerualNet(string nn);
    void setHardwareDistribution(vector<string>);
private:
    OpenVinoEnv vino;
};

#endif // PRETRAINEDNN_H
