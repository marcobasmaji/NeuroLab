//checked

#include "OpenCLLayer.hpp"

#include <iostream>

using namespace std;

OpenCLLayer::OpenCLLayer() {
	releaseCLObjectsManager = new ReleaseCLObjectsManager();
}
OpenCLLayer::~OpenCLLayer() {
	releaseResources();

	delete releaseCLObjectsManager;
}

void OpenCLLayer::computeForward(OpenCLEnvironment* openclEnvironment, size_t batchSize, size_t outputMaps) {
	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

	cl_uint workDim = 2;

	const size_t globalWorkSize[] = { batchSize, outputMaps };

	executeKernel(commandQueue, kernelFeedforward, workDim, globalWorkSize);
}
void OpenCLLayer::computeErrorComp(OpenCLEnvironment* openclEnvironment, size_t batchSize) {
	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

	cl_uint workDim = 1;

	const size_t globalWorkSize[] = { batchSize };

	executeKernel(commandQueue, kernelErrorComp, workDim, globalWorkSize);
}
void OpenCLLayer::computeWeightsUpdate(OpenCLEnvironment* openclEnvironment, size_t outputMaps) {
	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

	cl_uint workDim = 1;

	const size_t globalWorkSize[] = { outputMaps };

	executeKernel(commandQueue, kernelWeightsUpdate, workDim, globalWorkSize);
}

void* OpenCLLayer::enqueueReadBuffer(cl_command_queue commandQueue, size_t size, cl_mem mem) {
	cl_int error;

	void* returnValue = malloc(size);
	error = clEnqueueReadBuffer(commandQueue, mem, CL_TRUE, 0, size, returnValue, 0, NULL, NULL);

	if (error == CL_INVALID_COMMAND_QUEUE) {
		cerr << "Error in enqueueReadBuffer (CL_INVALID_COMMAND_QUEUE)." << endl;
	}
	else if (error == CL_INVALID_CONTEXT) {
		cerr << "Error in enqueueReadBuffer (CL_INVALID_CONTEXT)." << endl;
	}
	else if (error == CL_INVALID_MEM_OBJECT) {
		cerr << "Error in enqueueReadBuffer (CL_INVALID_MEM_OBJECT)." << endl;
	}
	else if (error == CL_INVALID_VALUE) {
		cerr << "Error in enqueueReadBuffer (CL_INVALID_VALUE)." << endl;
	}
	else if (error == CL_INVALID_EVENT_WAIT_LIST) {
		cerr << "Error in enqueueReadBuffer (CL_INVALID_EVENT_WAIT_LIST)." << endl;
	}
	else if (error == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
		cerr << "Error in enqueueReadBuffer (CL_MEM_OBJECT_ALLOCATION_FAILURE)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in enqueueReadBuffer (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in enqueueReadBuffer. Error is not specified!" << endl;
	}

	return returnValue;
}
void OpenCLLayer::enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data) {
	cl_int error = clEnqueueWriteBuffer(commandQueue, mem, CL_TRUE, 0, size, data, 0, NULL, NULL);

	if (error == CL_INVALID_COMMAND_QUEUE) {
		cerr << "Error in enqueueWriteBuffer (CL_INVALID_COMMAND_QUEUE)." << endl;
	}
	else if (error == CL_INVALID_CONTEXT) {
		cerr << "Error in enqueueWriteBuffer (CL_INVALID_CONTEXT)." << endl;
	}
	else if (error == CL_INVALID_MEM_OBJECT) {
		cerr << "Error in enqueueWriteBuffer (CL_INVALID_MEM_OBJECT) ." << endl;
	}
	else if (error == CL_INVALID_VALUE) {
		cerr << "Error in enqueueWriteBuffer (CL_INVALID_VALUE)." << endl;
	}
	else if (error == CL_INVALID_EVENT_WAIT_LIST) {
		cerr << "Error in enqueueWriteBuffer (CL_INVALID_EVENT_WAIT_LIST)." << endl;
	}
	else if (error == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
		cerr << "Error in enqueueWriteBuffer (CL_MEM_OBJECT_ALLOCATION_FAILURE)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in enqueueWriteBuffer (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in enqueueWriteBuffer. Error is not specified!" << endl;
	}
}

void OpenCLLayer::executeKernel(cl_command_queue commandQueue, cl_kernel kernel, cl_uint workDim, const size_t* globalWorkSize) {
	cl_int error = clEnqueueNDRangeKernel(commandQueue, kernel, workDim, NULL, globalWorkSize, NULL, 0, NULL, NULL);

	if (error == CL_INVALID_PROGRAM_EXECUTABLE) {
		cerr << "Error in executeKernel (CL_INVALID_PROGRAM_EXECUTABLE)." << endl;
	}
	else if (error == CL_INVALID_COMMAND_QUEUE) {
		cerr << "Error in executeKernel (CL_INVALID_COMMAND_QUEUE)." << endl;
	}
	else if (error == CL_INVALID_KERNEL) {
		cerr << "Error in executeKernel (CL_INVALID_KERNEL)." << endl;
	}
	else if (error == CL_INVALID_CONTEXT) {
		cerr << "Error in executeKernel (CL_INVALID_CONTEXT)." << endl;
	}
	else if (error == CL_INVALID_KERNEL_ARGS) {
		cerr << "Error in executeKernel (CL_INVALID_KERNEL_ARGS)." << endl;
	}
	else if (error == CL_INVALID_WORK_DIMENSION) {
		cerr << "Error in executeKernel (CL_INVALID_WORK_DIMENSION)." << endl;
	}
	else if (error == CL_INVALID_WORK_GROUP_SIZE) {
		cerr << "Error in executeKernel (CL_INVALID_WORK_GROUP_SIZE)." << endl;
	}
	else if (error == CL_INVALID_WORK_ITEM_SIZE) {
		cerr << "Error in executeKernel (CL_INVALID_WORK_ITEM_SIZE)." << endl;
	}
	else if (error == CL_INVALID_GLOBAL_OFFSET) {
		cerr << "Error in executeKernel (CL_INVALID_GLOBAL_OFFSET)." << endl;
	}
	else if (error == CL_OUT_OF_RESOURCES) {
		cerr << "Error in executeKernel (CL_OUT_OF_RESOURCES)." << endl;
	}
	else if (error == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
		cerr << "Error in executeKernel (CL_MEM_OBJECT_ALLOCATION_FAILURE)." << endl;
	}
	else if (error == CL_INVALID_EVENT_WAIT_LIST) {
		cerr << "Error in executeKernel (CL_INVALID_EVENT_WAIT_LIST)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in executeKernel (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in executeKernel. Error is not specified!" << endl;
	}
}

void OpenCLLayer::releaseResources() {
    if(memInputs!=nullptr)          releaseCLObjectsManager->releaseMemObject(memInputs);
    if(memOutputs!=nullptr)         releaseCLObjectsManager->releaseMemObject(memOutputs);
    if(memBiases!=nullptr)          releaseCLObjectsManager->releaseMemObject(memBiases);
    if(memWeights!=nullptr)         releaseCLObjectsManager->releaseMemObject(memWeights);
    if(memErrorInputs!=nullptr)     releaseCLObjectsManager->releaseMemObject(memErrorInputs);
    if(memErrorOutputs!=nullptr)    releaseCLObjectsManager->releaseMemObject(memErrorOutputs);

	releaseCLObjectsManager->releaseKernel(kernelFeedforward);
	releaseCLObjectsManager->releaseKernel(kernelErrorComp);
    if(kernelWeightsUpdate!=nullptr)  releaseCLObjectsManager->releaseKernel(kernelWeightsUpdate);

	releaseCLObjectsManager->releaseProgram(program);
}

//setters
void OpenCLLayer::setMemInputs(cl_mem memInputs) {
	if (this->memInputs) {
		releaseCLObjectsManager->releaseMemObject(this->memInputs);
	}

    this->memInputs = memInputs;
}
void OpenCLLayer::setMemOutputs(cl_mem memOutputs) {
	if (this->memOutputs) {
		releaseCLObjectsManager->releaseMemObject(this->memOutputs);
	}
	
	this->memOutputs = memOutputs; 
}
void OpenCLLayer::setMemBiases(cl_mem memBiases) {
	if (this->memBiases) {
		releaseCLObjectsManager->releaseMemObject(this->memBiases);
	}

	this->memBiases = memBiases; 
}
void OpenCLLayer::setMemWeights(cl_mem memWeights) {
	if (this->memWeights) {
		releaseCLObjectsManager->releaseMemObject(this->memWeights);
	}

	this->memWeights = memWeights; 
}
void OpenCLLayer::setMemErrorInputs(cl_mem memErrorInputs) {
	if (this->memErrorInputs) {
		releaseCLObjectsManager->releaseMemObject(this->memErrorInputs);
	}

	this->memErrorInputs = memErrorInputs; 
}
void OpenCLLayer::setMemErrorOutputs(cl_mem memErrorOutputs) {
	if (this->memErrorOutputs) {
		releaseCLObjectsManager->releaseMemObject(this->memErrorOutputs);
	}

	this->memErrorOutputs = memErrorOutputs; 
}

void OpenCLLayer::setFeedforwardKernel(cl_kernel kernelFeedforward) {
	if (this->kernelFeedforward) {
		releaseCLObjectsManager->releaseKernel(this->kernelFeedforward);
    }

	this->kernelFeedforward = kernelFeedforward;
}
void OpenCLLayer::setErrorCompKernel(cl_kernel kernelErrorComp) {
	if (this->kernelErrorComp) {
		releaseCLObjectsManager->releaseKernel(this->kernelErrorComp);
	}

	this->kernelErrorComp = kernelErrorComp;
}
void OpenCLLayer::setWeightsUpdateKernel(cl_kernel kernelWeightsUpdate) {
	if (this->kernelWeightsUpdate) {
		releaseCLObjectsManager->releaseKernel(this->kernelWeightsUpdate);
	}

	this->kernelWeightsUpdate = kernelWeightsUpdate;
}
void OpenCLLayer::setProgram(cl_program program) {
	if (this->program) {
		releaseCLObjectsManager->releaseProgram(this->program);
	}

	this->program = program;
}

void OpenCLLayer::setInputs(OpenCLEnvironment* openclEnvironment, float *inputs, int length) {
    size_t size = length * sizeof(float);
    cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

    enqueueWriteBuffer(commandQueue, memInputs, size, (void*) inputs);
}
void OpenCLLayer::setWeights(OpenCLEnvironment* openclEnvironment, float *weights, int length) {

	size_t size = length * sizeof(float);
	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

	enqueueWriteBuffer(commandQueue, memWeights, size, (void*) weights);
}
void OpenCLLayer::setBiases(OpenCLEnvironment* openclEnvironment, float* biases, int length) {

	size_t size = length * sizeof(float);
	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();

	enqueueWriteBuffer(commandQueue, memBiases, size, (void*)biases);
}
void OpenCLLayer::setOutputErrors(OpenCLEnvironment* openCLEnvironment, float* outputErrors, int length) {

	size_t size = length * sizeof(float);
	cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();

	enqueueWriteBuffer(commandQueue, memErrorOutputs, size, (void*)outputErrors);
}


void OpenCLLayer::setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue) {
	cl_int error = clSetKernelArg(kernel, index, argSize, argValue);

	if (error == CL_INVALID_KERNEL) {
		cerr << "Error in setKernelArg (CL_INVALID_KERNEL)." << endl;
	}
	else if (error == CL_INVALID_ARG_INDEX) {
		cerr << "Error in setKernelArg (CL_INVALID_ARG_INDEX)." << endl;
	}
	else if (error == CL_INVALID_ARG_VALUE) {
		cerr << "Error in setKernelArg (CL_INVALID_ARG_VALUE)." << endl;
	}
	else if (error == CL_INVALID_MEM_OBJECT) {
		cerr << "Error in setKernelArg (CL_INVALID_MEM_OBJECT)." << endl;
	}
	else if (error == CL_INVALID_SAMPLER) {
		cerr << "Error in setKernelArg (CL_INVALID_SAMPLER)." << endl;
	}
	else if (error == CL_INVALID_ARG_SIZE) {
		cerr << "Error in setKernelArg (CL_INVALID_ARG_SIZE)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in setKernelArg. Error is not specified!" << endl;
	}
}

void OpenCLLayer::setLearningRate(float learningRate) {
	setKernelArg(kernelWeightsUpdate, 0, sizeof(cl_float), &learningRate);
}

void OpenCLLayer::setPreviousOpenCLLayer(OpenCLLayer* previousOpenCLLayer) {
	cl_mem memInputs = previousOpenCLLayer->getMemOutputs();
	this->setMemInputs(memInputs);
	this->setKernelArg(this->kernelFeedforward, 0, sizeof(cl_mem), &memInputs);
	this->setKernelArg(this->kernelErrorComp, 2, sizeof(cl_mem), &memInputs);
	if (this->kernelWeightsUpdate) { this->setKernelArg(this->kernelWeightsUpdate, 1, sizeof(cl_mem), &memInputs); }
	
	cl_mem memErrorInputs = this->getMemErrorInputs();
	previousOpenCLLayer->setKernelArg(previousOpenCLLayer->getKernelErrorComp(), 1, sizeof(cl_mem),&memErrorInputs);
	if (previousOpenCLLayer->getKernelUpdateWeights()) { previousOpenCLLayer->setKernelArg(previousOpenCLLayer->getKernelUpdateWeights(), 2, sizeof(cl_mem), &memErrorInputs); }
}

//getters
cl_mem OpenCLLayer::getMemErrorInputs() { return memErrorInputs; }
cl_mem OpenCLLayer::getMemErrorOutputs() { return memErrorOutputs; }
cl_mem OpenCLLayer::getMemOutputs() { return memOutputs; }
cl_mem OpenCLLayer::getMemInputs() { return memInputs; }

cl_kernel OpenCLLayer::getKernelErrorComp() {
	return kernelErrorComp;
}
cl_kernel OpenCLLayer::getKernelUpdateWeights() {
	return kernelWeightsUpdate;
}

float* OpenCLLayer::getWeights(OpenCLEnvironment* openCLEnvironment, int length){
	size_t size = length;

    cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();
	float* weights = (float*)enqueueReadBuffer(commandQueue, size * sizeof(float), memWeights);

	return weights;	
}

float* OpenCLLayer::getErrors(OpenCLEnvironment* openclEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength) {
	size_t size = (size_t) ((size_t)batchSize * (size_t)outputMaps * (size_t)outputHeight * (size_t)outputWidth);

	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();
	float* outputs = (float*)enqueueReadBuffer(commandQueue, size * sizeof(float), memErrorOutputs);

	return outputs;
}
float* OpenCLLayer::getOutputs(OpenCLEnvironment* openclEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength){
	size_t size = (size_t)((size_t)batchSize * (size_t)outputMaps * (size_t)outputHeight * (size_t)outputWidth);

	cl_command_queue commandQueue = openclEnvironment->getCommandQueue();
	float* outputs = (float*) enqueueReadBuffer(commandQueue, size*sizeof(float), memOutputs);
    cerr<<"reached 1!!!"<<endl;



	return outputs;
}
