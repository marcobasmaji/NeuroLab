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

    viewController->train(dataSetDir, weightsDir, newWeightsDir);

    emit finished();
}
