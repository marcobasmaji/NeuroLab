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
	void train();
	void executeTransferLearning();
    void updateDataSet(vector<string> dataSet);
    void trainWithMnist();
    vector<pair<string,float>> getLabelWithProb(float prob[]);
private:
    vector<string> dataSet;
    OpenCLEnvironment* clEnv;
    //Layers
    ConvolutionLayer* conv1=nullptr;
    ReLULayer* relu1=nullptr;
    MaxPoolingLayer* max1=nullptr;
    ConvolutionLayer *conv2=nullptr;
    ReLULayer *relu2=nullptr;
    MaxPoolingLayer* max2=nullptr;
    DenseLayer* dense=nullptr;
    SoftmaxLayer* soft=nullptr;
    Loss* lossFunction=nullptr;

    static bool sortBySec(const pair<int,int> &a,
                  const pair<int,int> &b)
    {
        return (a.second > b.second);
    }

};
