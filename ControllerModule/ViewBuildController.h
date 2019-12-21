#ifndef VIEWBUILDCONTROLLER_H
#define VIEWBUILDCONTROLLER_H

#include<ViewModule/GUIBuilder.h>

class ViewBuildController
{
public:
    ViewBuildController(QApplication& app);
private:
    GUIBuilder* guiBuilder;
};

#endif // VIEWBUILDCONTROLLER_H
