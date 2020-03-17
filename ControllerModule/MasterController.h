#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H
#include <QApplication>
#include <string.h>
#include <iostream>
#include <list>
#include <iterator>
#include <ControllerModule/ViewController.h>
#include <ControllerModule/PredictionController.h>
#include <ControllerModule/NNController.h>
#include <ControllerModule/HardwareElement.h>
#include <ControllerModule/HardwareSurveillence.h>



using namespace std;

class MasterController
{

public:
    MasterController();
    void setPaths(vector<string> paths);
    void classify(string nn, string mode, vector<string> selectedHardware, int nrImages);
    void train(string weightsDir, string dataSetDir, string newWeightsDir);
    void getPrediction(const string net, const string mode, vector<string> hardware, int nrImages);
    void setNNType(string nn);
    void setMode(string mode);
    vector<string> getAvailableHardware();
    //void setAvailableHardware(const list<HardwareElement> &value);
    list<HardwareElement> getSelectedHardware() const;
    void setSelectedHardware(const list<HardwareElement> &value);

private:
    NNController nnObserver;
    ViewController viewObserver;
    PredictionController predictionObserver;
    string nnType;
    list<HardwareElement> selectedHardware;
    string mode;
    vector<string> imagePaths;
    list<pair<string,vector<string>>> results;

    void initControllers();
    string transfer(string guiName);
};

#endif // MASTERCONTROLLER_H
