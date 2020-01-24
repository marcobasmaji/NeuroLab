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
    this->displayAvailableHardware();
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
    vector<string> hardware = settings.getSelectedHardware();
    this->master->getPrediction(net, mode, hardware);
}

void ViewController::displayPrediction(vector<double> timeConsumption, vector<double> powerConsumption, double bandwidth, double flops) {

}

void ViewController::setNeuralNet(string nn)
{
    //master->setNNType(nn);
}

void ViewController::setOpMode(string mode)
{
   // master->setMode(mode);
}



void ViewController::setAvailableHardware(const list<string> &hardwareElements)
{
    availableHardware.clear();
    for(string hardware : hardwareElements){
        if(hardware.compare("Movidius") == 0 || hardware.compare("Movidius.1") == 0){
            availableHardware.push_back(MOV1);
        }

        if(hardware.compare("Movidius.2") == 0){
            availableHardware.push_back(MOV2);
        }
        if(hardware.compare("Movidius.3") == 0){
            availableHardware.push_back(MOV3);
        }

        if(hardware.compare("Movidius.4") == 0){
            availableHardware.push_back(MOV4);
        }

        if(hardware.compare("CPU") == 0){
            availableHardware.push_back(CPU);
        }

        if(hardware.compare("GPU") == 0){
            availableHardware.push_back(GPU);
        }

        if(hardware.compare("FPGA") == 0){
            availableHardware.push_back(FPGA);
        }
    }
}


void ViewController::displayAvailableHardware()
{
    setAvailableHardware({ "CPU"});
    mainWindow->disableHWCheckboxes();
    for(HardwareElement element : availableHardware){
       mainWindow->enableCheckbox(element);
    }

}
