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
#include <DataModule/Shape.h>
#include <DataModule/Result.h>
#include "../Tools/opencv2/include/opencv.hpp"
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
    list<Layer*> layers;
    //Layers
    //ConvolutionLayer* conv1;
    //ReLULayer* relu1;
    MaxPoolingLayer* max1;
    //ConvolutionLayer *conv2;
    //ReLULayer *relu2;
    MaxPoolingLayer* max2;
    DenseLayer* dense;
    SoftmaxLayer* soft;
    Loss* lossFunction;

    static bool sortBySec(const pair<int,int> &a,
                  const pair<int,int> &b)
    {
        return (a.second > b.second);
    }
    float *getPixelsFromPath(string path);

};
