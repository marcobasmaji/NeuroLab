#include "GUISettings.h"

GUISettings::GUISettings()
{
    //set default values:
    this->nn = "AlexNet";
    this->mode = "HighestPerfomance";
    this->nrImages = 0;
}

int GUISettings::getNrImages() const
{
    return nrImages;
}

void GUISettings::setNrImages(int value)
{
    nrImages += value;
}

vector<string> GUISettings::getHardware() const
{
    return hardware;
}

void GUISettings::setHardware(vector<HardwareElement> hardware)
{
    for (HardwareElement hw : hardware) {
        switch(hw){
        case MOV : this->hardware.push_back("Movidius");
            break;
        case MOV1 : this->hardware.push_back("Movidius.1");
            break;
        case MOV2 : this->hardware.push_back("Movidius.2");
            break;
        case MOV3: this->hardware.push_back("Movidius.3");
            break;
        case MOV4 : this->hardware.push_back("Movidius.4");
            break;
        case CPU : this->hardware.push_back("CPU");
            break;
        case GPU : this->hardware.push_back("GPU");
            break;
        case FPGA : this->hardware.push_back("FPGA");
            break;
        }
    }
}

string GUISettings::getMode() const
{
    return mode;
}

void GUISettings::setMode(const string &value)
{
    mode = value;
}

string GUISettings::getNn() const
{
    return nn;
}

void GUISettings::setNn(const string &value)
{
    nn = value;
}
