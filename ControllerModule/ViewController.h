#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include<ViewModule/GUI.h>
#include <string>
#include <iostream>
using namespace std;
// defining a class here to avoid having a loop of includes.
//forward declaration. Needed when wanting to connect back a class.
class MasterController;
class ViewController
{
public:
    ViewController(MasterController* partner);
    void updatePathList(list<string> paths);
    void handleClassifyRequest();
private:
    GUI gui;
    MasterController* master;
    list<string> l;

};

#endif // VIEWCONTROLLER_H



