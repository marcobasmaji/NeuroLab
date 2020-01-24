#include <NNModule/NeuralNet.h>
#include <iostream>
#include <vector>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp>
#include "../HardwareModule/OpenCL/HardwareType.cpp"
#include <DataModule/Shape.h>

#include <Tools/opencv2/include/opencv.hpp>

using namespace std;

class NeuroLabNet: public NeuralNet 
{
public:
    NeuroLabNet();
	void init();
	void classify();
	void train();
	void executeTransferLearning();
    void updateDataSet(vector<string> dataSet);
private:
    vector<string> dataSet;
    OpenCLEnvironment* clEnv;
};
