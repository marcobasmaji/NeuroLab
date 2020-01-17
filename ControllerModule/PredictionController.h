#ifndef PREDICTIONCONTROLLER_H
#define PREDICTIONCONTROLLER_H
#include<string.h>
#include <iostream>
#include <list>
#include <vector>

using namespace std;
class PredictionController
{
public:
    PredictionController();
    void calculatePrediction(int numberImg, const string net, const string mode, vector<string> hardware);
    vector<double> getTime();
    vector<double> getPower();
    double getBandwidth();
    double getFlops();
};

#endif // PREDICTIONCONTROLLER_H
