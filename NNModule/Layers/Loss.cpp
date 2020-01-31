#include "Loss.h"

Loss::Loss(size_t numInputs) : numInputs(numInputs)
{

}

Shape Loss::getPredictedDistributionGrad() const
{
    return predictedDistributionGrad;
}

float* Loss::getOutputError(float distribution[],string label)
{
    float derivative[numInputs];
    float targetDistribution[numInputs];
    QDir dir("/home/mo/classes");
    QStringList files = dir.entryList(QStringList(),QDir::Dirs);
    int i = 0;
    for(auto &item : files) {
        if(item.startsWith(".")){
            continue;
        }
        else if(item.toStdString()==label)
        {
            targetDistribution[i] = 1.0;
            i++;
        }
        else
        {
            targetDistribution[i] = 0.0;
            i++;
        }
    }
    // calculate
    float loss;
    for (size_t j=0; j<sizeof (targetDistribution);j++)
    {
        // calculate loss

        // derivative
        derivative[j] =-(distribution[j]/(1/targetDistribution[j]));
    }
    return derivative;

}
