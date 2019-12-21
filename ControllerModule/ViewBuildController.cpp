#include "ViewBuildController.h"
#include <QApplication>

ViewBuildController::ViewBuildController(QApplication& app)
{
    this->guiBuilder = new GUIBuilder(app);

}
