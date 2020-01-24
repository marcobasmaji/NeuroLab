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
    GUISettings()

    int getNrImages() const;
    void setNrImages(int value);

    vector<string> getHardware() const;
    void setHardware(vector<HardwareElement> hardware);

    string getMode() const;
    void setMode(const string &value);

    string getNn() const;
    void setNn(const string &value);

private:
    string nn;
    string mode;
    vector<string> hardware;
    int nrImages;
};

#endif // GUISETTINGS_H
