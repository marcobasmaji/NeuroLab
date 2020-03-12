#include "Loss.h"
#include <QtDebug>

Loss::Loss(size_t numInputs) : numInputs(numInputs)
{

}

float* Loss::getOutputError(float distribution[],string label)
{
    qDebug() << "reached 4" << endl;

    float* derivative = (float*)malloc(numInputs * sizeof (float*));
    float targetDistribution[numInputs];
    QDir dir("/home/mo/dataset");
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
    float loss = 0;
    for(unsigned int i=0;i<numInputs;i++)
    {
        loss += targetDistribution[i]*std::log(distribution[i]);
    }
    // save loss in case needed
    this->loss = -loss;
    for (size_t j=0; j<numInputs;j++)
    {
        // derivative
        derivative[j] =-(targetDistribution[j]/distribution[j]);
    }
    return derivative;

}
