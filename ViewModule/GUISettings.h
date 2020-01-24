#ifndef GUISETTINGS_H
#define GUISETTINGS_H
#include <string>
#include <iostream>
#include <vector>
#include <ControllerModule/HardwareElement.h>
using namespace std;

class GUISettings
{
public:
    GUISettings();
    void setNerualNet(string nn){
        this->nn = nn;
    }
    void setMode(string mode){
        this->mode = mode;
    }
    void setSelectedHardware(vector<HardwareElement> hardware) {
        //this->hardware = hardware;
    }
    string getNerualNet(){
        return nn;
    }
    string getMode(){
        return mode;
    }
    vector<string> getSelectedHardware() {
        return hardware;
    }

private:
    string nn;
    string mode;
    vector<string> hardware;
};

#endif // GUISETTINGS_H
