#ifndef NNCONTROLLER_H
#define NNCONTROLLER_H
#include<QApplication>
#include<NNModule/PretrainedNN.h>
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
    pair<string,vector<pair<string,float>>> getResults();
private:
    PretrainedNN pnn;
    vector<string> pathList;

};

#endif // NNCONTROLLER_H
