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
