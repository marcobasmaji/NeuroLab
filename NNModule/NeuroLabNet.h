#include <NNModule/NeuralNet.h>
#include <iostream>
#include <vector>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp>
#include "../HardwareModule/OpenCL/HardwareType.cpp"
#include <DataModule/Shape.h>
#include <DataModule/Result.h>
#include <opencv2/opencv.hpp>
#include <CL/cl.h>

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
    void trainWithCifar100();
private:
    vector<string> dataSet;
    OpenCLEnvironment* clEnv;
    list<Layer*> layers;
};
