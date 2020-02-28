#ifndef PREDICTIONVALUES_H
#define PREDICTIONVALUES_H
#include <string>
using namespace std;

class PredictionValues{


public:
    string power_consumption;
    string time;
    string flops;
    string bandwidth;
    string totalTime;
    string totalPowerConsumption;
    bool usedInDistribution() {
        if (this->power_consumption != "") {
            return true;
        }
        return false;
    };

};


#endif // PREDICTIONVALUES_H
