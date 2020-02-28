#ifndef LOSS_H
#define LOSS_H

#include <iostream>
#include "Layer.h"
#include <math.h>
#include <QApplication>
#include <QDir>

using namespace std;

class Loss
{
public:
    Loss(size_t numInputs);
    float *getOutputError(float distribution[],string label);

private:
    size_t numInputs;
    float loss;
};

#endif // LOSS_H
