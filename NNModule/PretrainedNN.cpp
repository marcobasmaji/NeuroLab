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

void PretrainedNN::setPlatforms(vector<pair<string, int> > platforms)
{
    vino.setDistribution(platforms);
}

void PretrainedNN::setNerualNet(string nn)
{
    vino.chooseNeuralNet(nn);
}


