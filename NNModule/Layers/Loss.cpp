#include "Loss.h"

Loss::Loss(size_t numInputs) : numInputs(numInputs)
{

}

Shape Loss::getPredictedDistributionGrad() const
{
    return predictedDistributionGrad;
}

float *Loss::getOutputError(float outputValues[], float targetValues[])
{
    float* errors = (float*)malloc(10*sizeof(float));

        float expectedValue = 0;

        for (int i = 0; i < 10; i++) {
            errors[i] = outputValues[i]-targetValues[i];
        }
        expectedValue = 1;

        errors[1] = expectedValue- outputValues[1];

        return errors;
}
