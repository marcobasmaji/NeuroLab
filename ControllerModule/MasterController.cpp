#include "MasterController.h"
#include <QApplication>
#include <QLabel>

MasterController::MasterController()
{
    initControllers();

}

void MasterController::initControllers() {
    viewObserver = new ViewBuildController();
    predictionObserver = new PredictionController();
    nnObserver = new NNController();
    imageParser = new ImagePareser();
}


