//checked

#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#define MAX_SOURCE_SIZE (0x100000)

#include <CL/cl.h>

#include "OpenCLLayer.hpp"
#include "OpenCLEnvironment.hpp"

class OpenCLLayerCreator {
private:
    const char* dirConvKernel = "../kernels/Conv.cl";
    const char* dirMaxPoolKernel = "../kernels/MaxPool.cl";
    const char* dirDenseKernel = "../kernels/Dense.cl";
    const char* dirReluKernel = "../kernels/Relu.cl";
    const char* dirPadKernel = "../kernels/Pad.cl";
    const char* dirSoftmaxKernel = "../kernels/Softmax.cl";

    void setZeros(cl_mem mem, cl_command_queue commandQueue, size_t size);
    void enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data);
    cl_mem createBuffer(cl_context context, cl_mem_flags flags, size_t size);
    cl_kernel createKernel(cl_program program, const char* functionName);
    cl_program createProgram(cl_context context, cl_device_id device, const char* dirKernel);

    const char* loadFile(const char* path, size_t* sourceSize);

    //setters
    void setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue);

public:
    OpenCLLayer* createReluLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth);
    OpenCLLayer* createPadLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int padHeight, int padWidth);
    OpenCLLayer* createConvLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputMaps, int outputHeight, int outputWidth, int kernelHeight, int kernelWidth, int strideHeight, int strideWidth);
    OpenCLLayer* createMaxPoolLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputHeight, int outputWidth, int poolHeight, int poolWidth, int strideHeight, int strideWidth);
    OpenCLLayer* createDenseLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputNeurons);
    OpenCLLayer* createSoftmaxLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth);
};

