#include "MasterController.h"
#include <QApplication>
#include <QLabel>

MasterController::MasterController(QApplication &app)
{
    ViewBuildController* viewObserver = new ViewBuildController(app);

}


