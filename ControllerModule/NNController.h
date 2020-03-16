#ifndef NNCONTROLLER_H
#define NNCONTROLLER_H
#include<QApplication>
#include<NNModule/PretrainedNN.h>
#include<NNModule/NeuroLabNet.h>
#include <iostream>
#include <list>
# include<string.h>

using namespace std;

class NNController
{
public:
    NNController();
    vector<Result> classify();
    //list<pair<string,vector<string>>>getResults();
    void setPathList(vector<string>);
    void setDistribution( vector<pair<string, int>> distribution);
    void setCurrentNN(string currentNN);
    void setHardwareDistribution(vector<string>);
    void trainNeuroLab(string,string);

private:
    PretrainedNN pnn;
    NeuroLabNet neuroLabNet;
    vector<string> pathList;
    string currentNN = "ALEXNET";

};

#endif // NNCONTROLLER_H
