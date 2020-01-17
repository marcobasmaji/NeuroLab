#include "NNController.h"
#include<list>
#include <QDebug>
#include <QFile>

NNController::NNController()
{

}
vector<Result> NNController::classify()
{
    qDebug()<<"classify called in NN"<<endl; // debug:

    return pnn.classify();
}


pair<string,vector<pair<string,float>>> NNController::getResults()
{
    pair<string,vector<pair<string,float>>> result;
    return result;
}

void NNController::setPathList(vector<string> list)
{
    //this->pathList = list;
    if(currentNN == "ALEXNET")
    {
    qDebug()<<"classify called in NNcontroller"<<endl; // debug: working
    pnn.setImagePaths(list);
    }
    else if(currentNN == "GOOGLENET")
    {
        pnn.setImagePaths(list);
    }
    else if(currentNN == "NEUROLABNET")
    {

    }
}

void NNController::setDistribution(vector<pair<string, int> > distribution) {

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
