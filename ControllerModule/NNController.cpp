#include "NNController.h"
#include<list>
#include <QDebug>

NNController::NNController()
{

}
void NNController::classify()
{
    qDebug()<<"classify called in NN"<<endl; // debug:
    alexnet.classify({""});
}

void NNController::updateDataSet(QStringList dataPaths)
{
    this->dataPaths = dataPaths;

}
