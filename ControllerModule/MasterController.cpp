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

void MasterController::classify(string nn, string mode, vector<string> selectedHardware, int nrImages, vector<pair<string, string>> hwNamesMap)
{
    qDebug()<<"classify called in Master"<<endl; // debug: working

    //-------------hier brauchen wir noch----------------------------------------------------------

    nnObserver.setCurrentNN(nn);

    qDebug()<<"master setting in classify 1"<<endl;
    for(string hw : selectedHardware){
        qDebug()<<QString::fromStdString(hw)<<endl;
    }
    DataResults predictionResults = predictionObserver.calculatePrediction(nrImages,nn,mode,selectedHardware);

    qDebug()<<"master setting in classify 2"<<endl;
    for(pair<string, int> hw : predictionResults.hardwareDistribution){
        qDebug()<<QString::fromStdString(hw.first)<<endl;
    }
    int count =0;
    vector<pair<string, int>>  hwDist;
    for(auto hD : predictionResults.hardwareDistribution){
        for(auto hwMap : hwNamesMap){
            if(hD.first.compare(hwMap.first) == 0){
                hwDist.push_back({hwMap.second, hD.second});
                qDebug()<<"Master distribution translation"<<QString::fromStdString(hwDist.back().first)<<endl; // debug: working
            }
        }
    }

    nnObserver.setDistribution(hwDist);
    //----------------------------------------------------------------------------------------------
    vector<Result> results = nnObserver.classify();
    viewObserver.displayResults(results);    
}

void MasterController::train(string weightsDir, string dataSetDir){
    //---------------this is needed----------
    //nnObserver.train(weightsDir,dataSetDir);
    //----------------------
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
