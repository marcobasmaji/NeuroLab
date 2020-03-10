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
    void setPlatforms(vector<pair<string, int> > platforms);
    vector<Result> classify();
    void setNerualNet(string nn);
private:
    OpenVinoEnv vino;
};

#endif // PRETRAINEDNN_H
