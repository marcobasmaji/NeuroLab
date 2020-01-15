#include "GUI.h"
#include <ViewModule/MainWindow.h>
#include<ControllerModule/ViewController.h>
#include<QDebug>

GUI::GUI(ViewController* partner)
{
    this->viewController = partner;
    // dummy arguments for QApplication
    char amessage[] = "this is it";
    char *pmessage = amessage;
    int argc = 0;
    char **argv = &pmessage;

    QApplication app(argc,argv);

    MainWindow w(nullptr,this);
    w.setWindowTitle("NeuroLab");
    w.resize(750,450);
    w.show();
    app.exec();

}
void GUI::loadPaths(list<string> paths)
{
    qDebug()<<"2"<<endl;
    this->viewController->updatePathList(paths);

}


void GUI::classifyImages()
{

    this->viewController->handleClassifyRequest();
}

void GUI::removeImages()
{
}
