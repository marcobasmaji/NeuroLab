#ifndef GUISETTINGS_H
#define GUISETTINGS_H
#include <string>
#include <iostream>
using namespace std;

class GUISettings
{
public:
    GUISettings();
    void setNerualNet(string nn){
        this->nnType = nn;
    }
private:
    string nnType;
};

#endif // GUISETTINGS_H
