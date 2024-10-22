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
        pnn.setImagePaths(pathList);
        pnn.setNeuralNet(currentNN);
        pnn.setPlatforms(distribution);

         pnn.classify();
         return pnn.getResults();
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

}

void NNController::setDistribution(vector<pair<string, int>> distribution) {

    this->distribution = distribution;

}

//void NNController::trainNeuroLab(string weightsDir, string dataSetDir, string newWeightsDir)
//{
//    neuroLabNet.train(weightsDir, dataSetDir, newWeightsDir);
//}

bool NNController::trainNeuroLab(string weightsDir, string dataSetDir, string newWeightsDir)
{
    bool res = neuroLabNet.train(weightsDir, dataSetDir, newWeightsDir);
    cerr<<res<<" nncontroller"<<endl;
    return res;
}

void NNController::setCurrentNN(string currentNN)
{
    this->currentNN = currentNN;
}
