#include <NNModule/NeuralNet.h>
#include <iostream>
#include <HardwareModule/OpenCL/OpenCLEnvironment.hpp>
#include <HardwareModule/OpenCL/OpenCLEnvironmentCreator.hpp>
#include "../HardwareModule/OpenCL/HardwareType.cpp"

using namespace std;

class NeuroLabNet: public NeuralNet 
{
public:
    NeuroLabNet();
	void init();
	void classify();
	void train();
	void executeTransferLearning();
private:

    OpenCLEnvironment* clEnv;
};
