#include "GUISettings.h"
#include <bits/stdc++.h>
#include <iostream>
#include <list>

GUISettings::GUISettings()
{
    //set default values:
    this->nn = "ALEXNET";
    this->mode = "HIGHEST_PERFORMANCE";
}

vector<string> GUISettings::getPaths() const{
    return paths;
}
void GUISettings::setPaths(const vector<string> &newPaths){
    if(paths.empty()){
        paths = newPaths;
        return;
    }

    for(string path : newPaths){
        paths.push_back(path);
    }
}

void GUISettings::removePath(string value){
    std::vector<string>::iterator foundvalue = std::find(paths.begin(), paths.end(), value);
    if (foundvalue != paths.end()){
        paths.erase(foundvalue);
    }
}

vector<string> GUISettings::getSelectedHardware() const
{
    return selectedHardware;
}

void GUISettings::setSelectedHardware(vector<HardwareElement> hardware)
{
    for (HardwareElement hw : hardware) {
        switch(hw){
        case MOV : this->selectedHardware.push_back("MYRIAD");
            break;
        case MOV1 : this->selectedHardware.push_back("MYRIAD.1");
            break;
        case MOV2 : this->selectedHardware.push_back("MYRIAD.2");
            break;
        case MOV3: this->selectedHardware.push_back("MYRIAD.3");
            break;
        case MOV4 : this->selectedHardware.push_back("MYRIAD.4");
            break;
        case CPU : this->selectedHardware.push_back("CPU");
            break;
        case GPU : this->selectedHardware.push_back("GPU");
            break;
        case FPGA : this->selectedHardware.push_back("FPGA");
            break;
        }
    }
}

void GUISettings::clearHardware(){
    selectedHardware.clear();
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

void GUISettings::unselectHardwareElement(string element) {
    auto itr = std::find(selectedHardware.begin(), selectedHardware.end(), element);
    if (itr != selectedHardware.end()) selectedHardware.erase(itr);
}

void GUISettings::selectHardwareElement(string element) {
    auto itr = std::find(selectedHardware.begin(), selectedHardware.end(), element);
    if (itr == selectedHardware.end()) selectedHardware.push_back(element);
};



