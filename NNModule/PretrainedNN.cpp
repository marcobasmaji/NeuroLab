#include "PretrainedNN.h"

PretrainedNN::PretrainedNN()
{

}

vector<Result> PretrainedNN::classify()
{
    return vino.classify();
}

void PretrainedNN::setImagePaths(vector<string> imagePaths)
{
    vino.setImageNames(imagePaths);
}

void PretrainedNN::setPlatforms(vector<string> platforms)
{
    vino.setPlatforms(platforms);
}

void PretrainedNN::setNerualNet(string nn)
{
    vino.chooseNeuralNet(nn);
}

void PretrainedNN::setHardwareDistribution(vector<string> distr)
{
    vino.setPlatforms(distr);
}
