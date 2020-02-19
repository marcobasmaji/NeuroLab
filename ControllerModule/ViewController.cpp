#include "ViewController.h"
#include <QApplication>
#include <ControllerModule/MasterController.h>
#include <QDebug>
#include <ViewModule/MainWindow.h>
#include <PredictionModule/Prediction.h>
#include <math.h>

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


void ViewController::removeImage(string imagePath){
    qDebug()<<"remove image "<<endl;
}

void ViewController::handleClassifyRequest(GUISettings settings)
{
    vector<string> paths = settings.getPaths();
    this->master->setPaths(paths);
    this->master->classify(settings.getNn(), settings.getMode(),  settings.getSelectedHardware(), paths.size());
}

void ViewController::displayResults(vector<Result> results)
{
    mainWindow->displayResults(results);
}

void ViewController::getPrediction(GUISettings settings)
{
    string mode = settings.getMode();
    string net = settings.getNn();
    vector<string> hardware = settings.getSelectedHardware();
    int nrImages = settings.getPaths().size();
    this->master->getPrediction(net, mode, hardware, nrImages);
}

PredictionValues *ViewController::parseHardware(string hw, vector<pair<string,double>> timeConsumption, vector<pair<string,double>> powerConsumption, vector<pair<string,double>> flops, vector<pair<string,double>> bandwidth) {
    PredictionValues *values = new PredictionValues();
    for (pair<string,double> time : timeConsumption) {
        if ((time.first).compare(hw) == 0) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << time.second;
            std::string time_string = stream.str();
            values->time = time_string;
        }
    }
    for (pair<string,double> power : powerConsumption) {
        if ((power.first).compare(hw) == 0) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << power.second;
            std::string power_string = stream.str();
            values->power_consumption = power_string;
        }
    }
    for (pair<string,double> flops : flops) {
        if ((flops.first).compare(hw) == 0) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << flops.second;
            std::string flops_string = stream.str();
            values->flops = flops_string;
        }
    }
    for (pair<string,double> bandwidth : bandwidth) {
        if ((bandwidth.first).compare(hw) == 0) {
            std::stringstream stream;
            stream << std::fixed << std::setprecision(2) << bandwidth.second;
            std::string bandwidth_string = stream.str();
            values->bandwidth = bandwidth_string;
        }
    }
    return values;

}

//display Prediction test the values in View
void ViewController::displayPrediction(double totalTime, double totalPowerConsumption, vector<pair<string,double>> timeConsumption, vector<pair<string,double>> powerConsumption, vector<pair<string,double>> flops, vector<pair<string,double>> bandwidth) {

    PredictionValues *cpu = parseHardware("CPU", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *gpu = parseHardware("GPU", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov1 = parseHardware("MYRIAD.1", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov2 = parseHardware("MYRIAD.2", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov3 = parseHardware("MYRIAD.3", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov4 = parseHardware("MYRIAD.4", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *fpga = parseHardware("FPGA", timeConsumption, powerConsumption, flops, bandwidth);
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << totalTime;
    std::string totalTime_string = stream.str();

    std::stringstream stream2;
    stream2 << std::fixed << std::setprecision(2) << totalPowerConsumption;
    std::string totalPowerConsumption_string = stream2.str();


    /*PredictionValues *cpu = parseHardware("CPU", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *gpu = parseHardware("GPU", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov1 = parseHardware("MYRIAD.1", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov2 = parseHardware("MYRIAD.2", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov3 = parseHardware("MYRIAD.3", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *mov4 = parseHardware("MYRIAD.4", timeConsumption, powerConsumption, flops, bandwidth);
    PredictionValues *fpga = parseHardware("FPGA", timeConsumption, powerConsumption, flops, bandwidth);
    string totalTime_string = "131";
    string totalPowerConsumption_string = "777";*/
    mainWindow->displayPrediction(totalTime_string, totalPowerConsumption_string, cpu, gpu, mov1, mov2, mov3, mov4, fpga);

}

void ViewController::setAvailableMovidius(int movidiusCounter) {
    switch (movidiusCounter) {
    case 1: availableHardware.push_back(MOV1); break;
    case 2: availableHardware.push_back(MOV2); break;
    case 3: availableHardware.push_back(MOV3); break;
    case 4: availableHardware.push_back(MOV4); break;
    }
}


void ViewController::setAvailableHardware(vector<string> &hardwareElements)
{
    availableHardware.clear();
    int movidiusCounter = 0;
    for(string hardware : hardwareElements){
        if(hardware.find("MYRIAD") != std::string::npos) {
            movidiusCounter++;
            setAvailableMovidius(movidiusCounter);
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
    vector<string> test;
    test = master->getAvailableHardware();
    setAvailableHardware(test);
    mainWindow->disableHWCheckboxes();
    for(HardwareElement element : availableHardware){
       mainWindow->enableCheckbox(element);
    }
}


