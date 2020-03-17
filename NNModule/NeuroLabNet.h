#include <NNModule/NeuralNet.h>
#include "Layers/ConvolutionLayer.h"
#include "Layers/ReLULayer.h"
#include "Layers/MaxPoolingLayer.h"
#include "Layers/SoftmaxLayer.h"
#include "Layers/DenseLayer.h"
#include "Layers/Loss.h"
#include <iostream>
#include <vector>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp>
#include "../HardwareModule/OpenCL/HardwareType.cpp"
#include <DataModule/Result.h>
#include <opencv2/opencv.hpp>
#include <CL/cl.h>
#include <fstream>
#include <QDir>

using namespace std;

class NeuroLabNet: public NeuralNet 
{
public:
    NeuroLabNet();
	void init();
    vector<Result> classify();
    void train(string weightsDir, string dataSetDir, string newWeightsDir);
	void executeTransferLearning();
    void updateDataSet(vector<string> dataSet);
    vector<pair<string,float>> getLabelWithProb(float prob[]);
private:
    vector<string> dataSet;
    OpenCLEnvironment* clEnv;
    //Layers
    OpenCLLayer* conv1;
    OpenCLLayer* conv2;
    OpenCLLayer* relu1;
    OpenCLLayer* relu2;
    OpenCLLayer* max1;
    OpenCLLayer* max2;
    OpenCLLayer* dense;
    OpenCLLayer* soft;
    //loss function
    Loss* lossFunction;

    static bool sortBySec(const pair<int,int> &a,
                  const pair<int,int> &b)
    {
        return (a.second > b.second);
    }

};
