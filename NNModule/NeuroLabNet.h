#pragma once

#include "HardwareModule/OpenCL/HardwareEnvironment.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironment.hpp"
#include "HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp"
#include "HardwareModule/OpenCL/OpenCLLayer.hpp"
#include "HardwareModule/OpenCL/OpenCLLayerCreator.hpp"
#include "NNModule/trainingItem.hpp"
#include "DataModule/Result.h"

#include <QString>
#include <vector>

using namespace std;

class NeuroLabNet{
private:
    OpenCLEnvironment* env;
    OpenCLEnvironmentCreator* envCreator;
    OpenCLLayerCreator* layerCreator;

    OpenCLLayer* conv1;
    OpenCLLayer* relu1;
    OpenCLLayer* max1;
    OpenCLLayer* conv2;
    OpenCLLayer* relu2;
    OpenCLLayer* max2;
    OpenCLLayer* dense;
    OpenCLLayer* softmax;

    vector<string> dataSet;

    void deleteRessources();
    void initNeuroLabNet();
    void loadWeightsAndBiases(string weightsDir);
    void saveWeightsAndBiases(string newWeightsDir);
    void saveArray(float* array, int length, string dir);
    void loadArray(float* array, int length, string dir);
    void loadAllImagePaths(string dataSetDir);
    vector<TrainingItem> getAllTrainingItems(string dataSetDir);
    vector<TrainingItem> shuffleDataset(vector<TrainingItem>vec);
    void calculateOutputErrors(int label, float* errors, float* outputs);
    void loadImageToArray(float* inputValues, string path);
    int predictedLabel(float*outputs);
    vector<pair<string,float>> getLabelWithProb(float prob[]);

public:
    NeuroLabNet();
    ~NeuroLabNet();

    void train(string weightsDir, string dataSetDir, string newWeightsDir);
    void updateDataSet(vector<string> dataSet);
    vector<Result> classify();
};
