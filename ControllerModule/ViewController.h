#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include<ViewModule/MainWindow.h>
#include<ViewModule/GUISettings.h>
#include <string>
#include <iostream>
#include <DataModule/Result.h>
using namespace std;
// defining a class here to avoid having a loop of includes.
//forward declaration. Needed when wanting to connect back a class.
class MasterController;
class MainWindow;
class ViewController
{
public:
    ViewController(MasterController * partner);
    void updatePathList(vector<string> paths);
    void handleClassifyRequest();
    void displayResults(vector<Result>);
    void getPrediction(GUISettings settings);
    void displayPrediction(vector<double> timeConsumption, vector<double> powerConsumption, double bandwidth, double flops);
private:
    //MainWindow* mainWindow;
    MasterController* master;
    MainWindow *mainWindow;
    list<string> l;


};

#endif // VIEWCONTROLLER_H



