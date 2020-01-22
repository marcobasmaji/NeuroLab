#include "ViewController.h"
#include <QApplication>
#include<ControllerModule/MasterController.h>
#include<QDebug>
#include <ViewModule/MainWindow.h>

ViewController::ViewController(MasterController* partner)
{
    char amessage[] = "this is it";
        char *pmessage = amessage;
        int argc = 0;
        char **argv = &pmessage;
        QApplication app(argc,argv);

    this->master= partner;
    mainWindow = new MainWindow(nullptr,this);
    mainWindow->setWindowTitle("NeuroLab");
    mainWindow->show();

    app.exec();
}
void ViewController::updatePathList(vector<string> paths)

{
    qDebug()<<"load in ViewCont"<<endl;
    this->master->setPaths(paths);


}

void ViewController::handleClassifyRequest()
{

    this->master->classify();
}

void ViewController::displayResults(vector<Result> results)
{
    mainWindow->displayResults(results);
}

void ViewController::getPrediction(GUISettings settings)
{
    string mode = settings.getMode();
    string net = settings.getNerualNet();
    vector<string> hardware = settings.gettHardware();
    this->master->getPrediction(net, mode, hardware);
}

void ViewController::displayPrediction(vector<double> timeConsumption, vector<double> powerConsumption, double bandwidth, double flops) {

}

void ViewController::setNeuralNet(string nn)
{

}

void ViewController::setOpMode(string mode)
{

}

void ViewController::setHardwareDist(vector<string> hardwareDist)
{

}
