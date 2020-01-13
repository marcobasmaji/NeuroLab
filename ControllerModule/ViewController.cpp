#include "ViewController.h"
#include <QApplication>
#include<ControllerModule/MasterController.h>

ViewController::ViewController(MasterController* partner)
{
   this->gui = new GUI(this);
   this->master = partner;
}
