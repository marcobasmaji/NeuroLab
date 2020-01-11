//checked

#pragma once

#include "CL/cl.h"

#include "OpenCLEnvironment.hpp"

class OpenCLLayer {
private:
	cl_mem memInputs = nullptr;
	cl_mem memOutputs = nullptr;
	cl_mem memBiases = nullptr;
	cl_mem memWeights = nullptr;
	cl_mem memErrorInputs = nullptr;
	cl_mem memErrorOutputs = nullptr;

	cl_program program = nullptr;
	cl_kernel kernelFeedforward = nullptr;
	cl_kernel kernelErrorComp = nullptr;
	cl_kernel kernelWeightsUpdate = nullptr;

	ReleaseCLObjectsManager* releaseCLObjectsManager=nullptr;

	void executeKernel(cl_command_queue commandQueue, cl_kernel kernel, cl_uint workDim, const size_t* globalWorkSize);
	
	void setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue);

	void* enqueueReadBuffer(cl_command_queue commandQueue, size_t size, cl_mem mem);
	void enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data);

	void releaseResources();

public:
	OpenCLLayer();
	~OpenCLLayer();

	void computeForward(OpenCLEnvironment* openCLEnvironment, size_t batchSize, size_t outputMaps);
	void computeErrorComp(OpenCLEnvironment* openCLEnvironment, size_t batchSize);
	void computeWeightsUpdate(OpenCLEnvironment* openCLEnvironment, size_t outputMaps);

	//setters
	void setMemInputs(cl_mem memInputs);
	void setMemOutputs(cl_mem memOutputs);
	void setMemBiases(cl_mem memBiases);
	void setMemWeights(cl_mem memWeights);
	void setMemErrorInputs(cl_mem memErrorInputs);
	void setMemErrorOutputs(cl_mem memErrorOutputs);

	void setFeedforwardKernel(cl_kernel kernelFeedforward);
	void setErrorCompKernel(cl_kernel kernelErrorComp);
	void setWeightsUpdateKernel(cl_kernel kernelWeightsUpdate);

	void setProgram(cl_program program);
	
	void setPreviousOpenCLLayer(OpenCLLayer* previousOpenCLLayer);

	void setInputs(OpenCLEnvironment* openCLEnvironment, float* input, int length);
	void setWeights(OpenCLEnvironment* openCLEnvironment, float* weights, int length);
	void setBiases(OpenCLEnvironment* openCLEnvironment, float* biases, int length);
	void setOutputErrors(OpenCLEnvironment* openCLEnvironment, float* outputErrors, int length);
	void setLearningRate(float learningRate);

	//getters
	cl_mem getMemErrorInputs();
	cl_mem getMemErrorOutputs();
	cl_mem getMemOutputs();
	cl_mem getMemInputs();

	cl_kernel getKernelErrorComp();
	cl_kernel getKernelUpdateWeights();

	float* getErrors(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength);
	float* getOutputs(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength);
};
