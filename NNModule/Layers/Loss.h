#ifndef LOSS_H
#define LOSS_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"
#include <math.h>
#include <QApplication>
#include <QDir>

using namespace std;

class Loss : public Layer
{
public:
    Loss(size_t numInputs);
    Shape getPredictedDistributionGrad() const;
    float *getOutputError(float distribution[],string label);

private:
    size_t numInputs;
    Shape predictedDistribution;
    Shape actualDistribution;

    double loss;

    Shape predictedDistributionGrad;
};

#endif // LOSS_H
