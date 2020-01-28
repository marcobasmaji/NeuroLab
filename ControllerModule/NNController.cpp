#include "NNController.h"
#include <list>
#include <QDebug>
#include <QFile>

NNController::NNController()
{

}
vector<Result> NNController::classify()
{
    qDebug()<<"classify called in NN"<<endl; // debug:

    if(currentNN == "ALEXNET")
    {
        pnn.setImagePaths(pathList);
        return pnn.classify();
    }
    else if(currentNN == "GOOGLENET")
    {
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

}

void NNController::setHardwareDistribution(vector<string> distr)
{
    if(currentNN == "ALEXNET")
    {
        pnn.setHardwareDistribution(distr);
    }
    else if(currentNN == "GOOGLENET")
    {
        pnn.setHardwareDistribution(distr);
    }
    else if(currentNN == "NEUROLABNET")
    {
        // can we run our net on other platforms than CPU ?
    }
    else
    {
    }
}

void NNController::setCurrentNN(string currentNN)
{
    this->currentNN = currentNN;
}
