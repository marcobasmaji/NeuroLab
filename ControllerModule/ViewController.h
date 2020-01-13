#ifndef VIEWCONTROLLER_H
#define VIEWCONTROLLER_H

#include<ViewModule/GUI.h>
class MasterController;
class ViewController
{
public:
    ViewController(MasterController* partner);
private:
    GUI* gui;
    MasterController* master;

};

#endif // VIEWCONTROLLER_H
