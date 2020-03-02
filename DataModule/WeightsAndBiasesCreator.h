#ifndef WEIGHTSCREATOR_H
#define WEIGHTSCREATOR_H
#include <stdlib.h>
#include <random>
#include <iostream>
#include <fstream>

using namespace std;

class WeightsAndBiasesCreator
{

private:
    int outputMaps = 0;
    int inputMaps = 0;
    int kernelHeight = 0;
    int kernelWidth = 0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution;//default mean = 0 and stdev = 1, so normal distribution
    double random;
    string dir;

    void save(vector<float> values, string dir);
    vector<float> createWeights();
    vector<float> createBias();
    int calculateId(int outputMap, int inputMap, int kernelY, int kernelX);
    int calculateWeightId(int inputMaps, int inputHeight, int inputWidth, int outputNeuron, int inputMap, int y, int x);

public:
    WeightsAndBiasesCreator(int outputMaps, int inputMaps, int kernelHeight, int kernelWidth, int seed);
    void createWeightsFile(string fileName);
    void createBiasFile(string fileName);
    void updateWeights();
    void updateBias();
};

#endif // WEIGHTSCREATOR_H
