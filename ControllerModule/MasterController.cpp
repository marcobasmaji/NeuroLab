#include "MasterController.h"
#include <QApplication>
#include <QLabel>
#include <QDebug>

MasterController::MasterController() : viewObserver(this)
{
    initControllers();

}

void MasterController::initControllers() {

}
void MasterController::setPaths(list<string> paths)
{
    qDebug()<<"4"<<endl;

    imagePaths = &paths;
    cout<< imagePaths->back();
    qDebug()<<"whaaaaaaat"<<endl;

}

void MasterController::startClassification()
{

    qDebug()<<"classify called in Master"<<endl; // debug: working.
    //QStringList* l = {"ss","ss"};
    //this->nnObserver->updateDataSet(l);
    nnObserver.classify();

}
