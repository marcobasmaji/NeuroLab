#ifndef GUIREQUESTHANDLER_H
#define GUIREQUESTHANDLER_H
#include<QStringList>
#include<ControllerModule/ViewRequestController.h>
#include<QMainWindow>

class GUIRequestHandler
{
public:
    GUIRequestHandler();
    void loadImages();
    void removeImages();
    void classifyImages();
private:
    QStringList paths;
    ViewRequestController VRCObserver;
};

#endif // GUIREQUESTHANDLER_H
