#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include<ViewModule/GUISettings.h>
#include<ViewModule/PredictionValues.h>
#include <string>
#include <stdio.h>
#include <string.h>
#include <iostream>
#include <DataModule/Result.h>
#include <ControllerModule/HardwareElement.h>
#include <list>
#include <iomanip>

using namespace std;
// defining a class here to avoid having a loop of includes.
//forward declaration. Needed when wanting to connect back a class.
class MasterController;
class MainWindow;
class ViewController
{
public:
    ViewController(MasterController * partner);
    vector <pair<string, string>> hwNamesMap;
    void handleClassifyRequest(GUISettings settings);
    void displayResults(vector<Result>);
    void getPrediction(GUISettings settings);
    void displayPrediction(double totalTime, double totalPowerConsumption, vector<pair<string,double>> timeConsumption, vector<pair<string,double>> powerConsumption, vector<pair<string,double>> flops, vector<pair<string,double>> bandwidth);
    void setHardwareDist(vector<string> hardwareDist);
    list<HardwareElement> availableHardware;
    void setAvailableHardware(vector<string> &hardwareElements);
    void displayAvailableHardware();
    void train(string weightsDir, string dataSetDir, string newWeightsDir);

    void showErrorMessage(string mes);
private:
    //MainWindow* mainWindow;
    MasterController* master;
    MainWindow *mainWindow;
    //WellcomePanel panel;
    list<string> l;
    PredictionValues *parseHardware(string hw, vector<pair<string,double>> timeConsumption, vector<pair<string,double>> powerConsumption,
                                    vector<pair<string,double>> flops, vector<pair<string,double>> bandwidth);


    void setAvailableMovidius(int movidiusCounter);
};

#endif // VIEWCONTROLLER_H



