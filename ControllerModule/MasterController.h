#ifndef MASTERCONTROLLER_H
#define MASTERCONTROLLER_H
#include <QApplication>
#include<string.h>
#include <iostream>
#include <list>
#include <iterator>
#include <ControllerModule/ViewBuildController.h>
#include <ControllerModule/PredictionController.h>
#include <ControllerModule/NNController.h>
#include <ControllerModule/ImagePareser.h>

using namespace std;

class MasterController
{

public:
    MasterController();

private:
    ViewBuildController* viewObserver;
    PredictionController* predictionObserver;
    NNController* nnObserver;
    ImagePareser* imageParser;
    string nnType;
    list<string> selectedHardware;
    string mode;
    list<string> imagePaths;
    void initControllers();
};

#endif // MASTERCONTROLLER_H
