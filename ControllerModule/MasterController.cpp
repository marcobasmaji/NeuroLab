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
    qDebug()<<"load in master"<<endl;

}

void MasterController::classify()
{

    qDebug()<<"classify called in Master"<<endl; // debug: working.
    //QStringList* l = {"ss","ss"};
    //this->nnObserver->updateDataSet(l);

    //nnObserver.setPathList(*imagePaths);
    nnObserver.classify();
    //results = nnObserver.getResults(); crashes

}
void MasterController::getPrediction(const string net, const string mode, vector<string> hardware)
{
    predictionObserver.calculatePrediction(this->imagePaths->size() ,net, mode,hardware);
    vector<double> timeConsumption = predictionObserver.getTime();
    vector<double> powerConsumption = predictionObserver.getPower();
    double bandwidth = predictionObserver.getBandwidth();
    double flops = predictionObserver.getFlops();
    // analog for powerconsumption
    vector<pair<string, int>> distribution;
    nnObserver.setDistribution(distribution);
    viewObserver.displayPrediction(timeConsumption, powerConsumption, bandwidth, flops);
}
