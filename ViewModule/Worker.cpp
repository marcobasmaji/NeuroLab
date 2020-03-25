#include "Worker.h"

// --- CONSTRUCTOR ---
Worker::Worker(string dataSetDir, string weightsDir, string newWeightsDir, ViewController *viewController)
{
    this->dataSetDir = dataSetDir;
    this->weightsDir = weightsDir;
    this->newWeightsDir = newWeightsDir;
    this->viewController = viewController;
}

// --- DECONSTRUCTOR ---
Worker::~Worker() {
    dataSetDir.clear();
    weightsDir.clear();
    newWeightsDir.clear();
}

// --- PROCESS ---
// Start processing data.
void Worker::process() {

    bool res;
    res = viewController->train(dataSetDir, weightsDir, newWeightsDir);
    if(res == false){
        emit error("The selected data set directory and/or weights directory are not correct. Please try again!");
    }

    emit finished();
}
