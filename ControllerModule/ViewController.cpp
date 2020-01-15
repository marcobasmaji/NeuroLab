#include "ViewController.h"
#include <QApplication>
#include<ControllerModule/MasterController.h>
#include<QDebug>

ViewController::ViewController(MasterController* partner) : gui(this)
{
   this->master = partner;
}
void ViewController::updatePathList(list<string> paths)

{
    qDebug()<<"3"<<endl;
    this->master->setPaths(paths);


}

void ViewController::handleClassifyRequest()
{

    this->master->startClassification();
}
