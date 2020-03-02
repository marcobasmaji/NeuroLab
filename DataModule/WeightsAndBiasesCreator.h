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
    WeightsAndBiasesCreator();

    /*
     * @brief used to create first weights file
     * @param fileName name of the new file
     * @param dir the selected directory
    */
    string createWeightsFile(string fileName, string dir);

    /*
     * @brief used to create first weights file
     * @param fileName name of the new file
     * @param weights the weights in matrix form
     * @param size the size of each row
    */
    void updateWeightsFile(string filePath, vector<vector<float>> weights, int size);

    /*
     * @brief used to create first weights file
     * @param fileName name of the new file
     * @param weights the list of weights values for one-dimensional tensor
    */
    void updateWeightsFile(string filePath, vector<float> weights);

    void createBiasFile(string fileName, string dir);
    void updateWeights();
    void updateBias();
};

#endif // WEIGHTSCREATOR_H
