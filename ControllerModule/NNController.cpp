#include "NNController.h"
#include<list>
#include <QDebug>

NNController::NNController()
{

}
void NNController::classify()
{
    qDebug()<<"classify called in NN"<<endl; // debug:
    pnn.classify({""});
}

void NNController::updateDataSet(QStringList dataPaths)
{
    this->dataPaths = dataPaths;

}

list<pair<string,vector<string>>> NNController::getResults()
{
    list<pair<string,vector<string>>> result;
    result.push_back({"path",{"result1","result2"}});
    return result;
}

void NNController::setPathList(list<string> list)
{
    this->pathList = list;
}

void NNController::setDistribution(vector<pair<string, int> > distribution) {

}
