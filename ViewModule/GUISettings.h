    #ifndef GUISETTINGS_H
#define GUISETTINGS_H
#include <string>
#include <iostream>
#include <vector>
#include <ControllerModule/HardwareElement.h>
#include <algorithm>
using namespace std;

class GUISettings
{
public:
    GUISettings();

    vector<string> getSelectedHardware() const;
    void setSelectedHardware(vector<HardwareElement> selectedHardware);

    string getMode() const;
    void setMode(const string &value);

    string getNn() const;
    void setNn(const string &value);

    vector<string> getPaths() const;
    void setPaths(const vector<string> &value);
    void removePath(string value);

    void clearHardware();

    void unselectHardwareElement(string element);
    void selectHardwareElement(string element);

private:
    string nn;
    string mode;
    vector<string> selectedHardware;
    vector<string> paths;
};

#endif // GUISETTINGS_H
