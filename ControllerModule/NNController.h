#ifndef NNCONTROLLER_H
#define NNCONTROLLER_H
#include<QApplication>
#include<NNModule/AlexNet.h>
class NNController
{
public:
    NNController();
    void classify();
    void updateDataSet(QStringList dataPaths);
private:
    QStringList dataPaths;
    AlexNet alexnet;
};

#endif // NNCONTROLLER_H
