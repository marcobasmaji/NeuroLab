#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H
#include <QApplication>
#include<string.h>
#include <iostream>
#include <list>
#include <iterator>
#include <ControllerModule/ViewController.h>
#include <ControllerModule/PredictionController.h>
#include <ControllerModule/NNController.h>
#include <ControllerModule/ImagePareser.h>
#include <ControllerModule/HardwareElement.h>


using namespace std;

class MasterController
{

public:
    MasterController();
    void setPaths(vector<string> paths);
    void classify();
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
    ImagePareser imageParser;
    string nnType;
    list<HardwareElement> selectedHardware;
    //list<HardwareElement> availableHardware;// in viewcontroller gesetzt
    string mode;
    //list<string> imagePaths;
    vector<string> imagePaths;
    list<pair<string,vector<string>>> results;

    void initControllers();
};

#endif // MASTERCONTROLLER_H
