#include "MasterController.h"
#include <QApplication>
#include <QLabel>
#include <QDebug>
#include "DataModule/Result.h"
#include "Tools/openvino/include/inference_engine.hpp"

MasterController::MasterController() : viewObserver(this)
{
}
void MasterController::setPaths(vector<string> paths)
{
    this->nnObserver.setPathList(paths);
    //this->imagePaths = paths;
    // cout<< imagePaths->back()
    qDebug()<<"load in master"<<endl; //ok

}

void MasterController::classify(string nn, string mode, vector<string> selectedHardware, int nrImages)
{
    qDebug()<<"classify called in Master"<<endl; // debug: working

    //-------------hier brauchen wir noch----------------------------------------------------------

    nnObserver.setCurrentNN(nn);
    DataResults predictionResults = predictionObserver.calculatePrediction(nrImages,nn,mode,selectedHardware);
    nnObserver.setDistribution(predictionResults.hardwareDistribution);
    //----------------------------------------------------------------------------------------------
    vector<Result> results = nnObserver.classify();
    viewObserver.displayResults(results);    
}
void MasterController::getPrediction(const string net, const string mode, vector<string> hardware , int nrImages)
{
    // analog for powerconsumption
    //vector<pair<string, int>> distribution;
    //nnObserver.setDistribution(distribution);
    //viewObserver.displayPrediction(timeConsumption, powerConsumption, bandwidth, flops);

    DataResults predictionResults = predictionObserver.calculatePrediction(nrImages, net, mode, hardware);

    viewObserver.displayPrediction(predictionResults.TotalTime, predictionResults.TotalPowerConsumption, predictionResults.Times, predictionResults.PowerConsumption, predictionResults.Flops, predictionResults.Bandwidth);
}

/*
 *  check only cpu, fpga, movidius stick availability:
 */


vector<string> MasterController::getAvailableHardware()
{

    //InferenceEngine::Core core;
    //return core.GetAvailableDevices();
     HardwareSurveillence surv;
     vector<string> d = surv.checkAvailableHardware();
    //vector<string> d = checkWithOpenVino();
    //for(string device : d){
         //devices.push_back(device);
    //}
    //d.push_back("GPU");
     return d;
   /* InferenceEngine::Core core;
    return core.GetAvailableDevices();*/

}

list<HardwareElement> MasterController::getSelectedHardware() const
{
    return selectedHardware;
}

void MasterController::setSelectedHardware(const list<HardwareElement> &value)
{
    selectedHardware = value;
}

void MasterController::setNNType(string nn)
{
    nnObserver.setCurrentNN(nn);
}
