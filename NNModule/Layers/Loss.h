#ifndef LOSS_H
#define LOSS_H

#include <iostream>
#include <DataModule/Shape.h>
#include "Layer.h"

class Loss : public Layer
{
public:
    Loss(size_t numInputs);
    Shape getPredictedDistributionGrad() const;

private:
    size_t numInputs;
    Shape predictedDistribution;
    Shape actualDistribution;

    double loss;

    Shape predictedDistributionGrad;
};

#endif // LOSS_H
