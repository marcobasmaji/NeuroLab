#include "NNController.h"
#include <list>
#include <QDebug>
#include <QFile>

NNController::NNController()
{

}
vector<Result> NNController::classify()
{
    if(currentNN == "ALEXNET")
    {
        pnn.setNerualNet("ALEXNET");
        pnn.setImagePaths(pathList);
        return pnn.classify();
    }
    else if(currentNN == "GOOGLENET")
    {
        pnn.setNerualNet("GOOGLENET");
        pnn.setImagePaths(pathList);
        return pnn.classify();
    }
    else if(currentNN == "NEUROLABNET")
    {
        neuroLabNet.updateDataSet(pathList);
        return neuroLabNet.classify();
    }
    else
    {
        return {};
    }
}

void NNController::setPathList(vector<string> list)
{
    this->pathList = list;

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
}
