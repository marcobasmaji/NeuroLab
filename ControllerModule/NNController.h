#ifndef NNCONTROLLER_H
#define NNCONTROLLER_H
#include<QApplication>
#include<NNModule/AlexNet.h>
#include <iostream>
#include <list>
# include<string.h>

using namespace std;

class NNController
{
public:
    NNController();
    void classify();
    void updateDataSet(QStringList dataPaths);
    list<pair<string,vector<string>>>getResults();
    void setPathList(list<string>);
    void setDistribution( vector<pair<string, int>> distribution);
private:
    QStringList dataPaths;
    AlexNet pnn;
    list<string> pathList;

};

#endif // NNCONTROLLER_H
