#include "Loss.h"

Loss::Loss(size_t numInputs) : numInputs(numInputs)
{

}

Shape Loss::getPredictedDistributionGrad() const
{
    return predictedDistributionGrad;
}
