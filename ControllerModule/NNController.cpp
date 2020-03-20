#include "NNController.h"
#include <list>
#include <QDebug>
#include <QFile>

NNController::NNController()
{

}
vector<Result> NNController::classify()
{
    cerr<<"NNController nn "<<currentNN<<endl;
    if(currentNN.compare("ALEXNET") == 0  || currentNN.compare("GOOGLENET") == 0)
    {
        return pnn.classify();
    }
    else if(currentNN.compare("NEUROLABNET") == 0)
    {
        neuroLabNet.updateDataSet(pathList);
        return neuroLabNet.classify();
    }
    return {};
}

void NNController::setPathList(vector<string> list)
{
    this->pathList = list;
    pnn.setImagePaths(list);

}

void NNController::setDistribution(vector<pair<string, int> > distribution) {

    this->pnn.setPlatforms(distribution);

}

void NNController::setHardwareDistribution(vector<string> distr)
{

}

void NNController::trainNeuroLab(string weightsDir, string dataSetDir, string newWeightsDir)
{
    neuroLabNet.train(weightsDir, dataSetDir, newWeightsDir);
}

void NNController::setCurrentNN(string currentNN)
{
    this->currentNN = currentNN;
    pnn.setNerualNet(currentNN);
}
