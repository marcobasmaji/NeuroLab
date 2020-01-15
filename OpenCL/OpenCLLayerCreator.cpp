//checked

#include <iostream>
#include <fstream>

#include "OpenCLLayerCreator.hpp"

cl_mem OpenCLLayerCreator::createBuffer(cl_context context, cl_mem_flags flags, size_t size) {
    cl_int error;

    cl_mem buffer = clCreateBuffer(context, flags, size, NULL, &error);

    if (error == CL_INVALID_CONTEXT) {
        cerr << "Fehler in createBuffer (CL_INVALID_CONTEXT)" << endl;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in createBuffer (CL_INVALID_VALUE)." << endl;
    }
    else if (error == CL_INVALID_BUFFER_SIZE) {
        cerr << "Error in createBuffer (CL_INVALID_BUFFER_SIZE)." << endl;
    }
    else if (error == CL_INVALID_HOST_PTR) {
        cerr << "Error in createBuffer (CL_INVALID_HOST_PTR)." << endl;
    }
    else if (error == CL_MEM_OBJECT_ALLOCATION_FAILURE) {
        cerr << "Error in createBuffer (CL_MEM_OBJECT_ALLOCATION_FAILURE)." << endl;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in createBuffer (CL_OUT_OF_HOST_MEMORY)." << endl;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in createBuffer. Error is not specified!" << endl;
    }

    return buffer;
}
cl_kernel OpenCLLayerCreator::createKernel(cl_program program, const char* functionName) {
    cl_int error;

    cl_kernel kernel = clCreateKernel(program, functionName, &error);

    if (error == CL_INVALID_PROGRAM) {
        cerr << "Error in createKernel (CL_INVALID_PROGRAM)." << endl;
    }
    else if (error == CL_INVALID_PROGRAM_EXECUTABLE) {
        cerr << "Error in createKernel (CL_INVALID_PROGRAM_EXECUTABLE)." << endl;
    }
    else if (error == CL_INVALID_KERNEL_NAME) {
        cerr << "Error in createKernel (CL_INVALID_KERNEL_NAME)." << endl;
    }
    else if (error == CL_INVALID_KERNEL_DEFINITION) {
        cerr << "Error in createKernel (CL_INVALID_KERNEL_DEFINITION)." << endl;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in createKernel (CL_INVALID_VALUE)." << endl;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in createKernel (CL_OUT_OF_HOST_MEMORY)." << endl;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in createKernel. Error is not specified!" << endl;
    }

    return kernel;
}
string OpenCLLayerCreator::loadFile(const char *path) {
	ifstream in(path);
	string contents((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

	return contents;
}
cl_program OpenCLLayerCreator::createProgram(cl_context context, cl_device_id device, const char* dirKernel) {
    cl_int error;

    string content = loadFile(dirKernel);
    size_t sourceSize=content.length();
    const char*data=content.c_str();

    cl_program program = clCreateProgramWithSource(context, 1, (const char**)&data, (const size_t*)&sourceSize, &error);

    if (error == CL_INVALID_CONTEXT) {
        cerr << "Fehler in createProgramWithSource (CL_INVALID_CONTEXT)." << endl;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in createProgramWithSource (CL_INVALID_VALUE)." << endl;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in createProgramWithSource (CL_OUT_OF_HOST_MEMORY)." << endl;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in createProgramWithSource. Error is not specified!" << endl;
    }

    error = clBuildProgram(program, 1, &device, NULL, NULL, NULL);

    if (error == CL_INVALID_PROGRAM) {
        cerr << "Fehler in buildProgram (CL_INVALID_PROGRAM)." << endl;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in buildProgram (CL_INVALID_VALUE)." << endl;
    }
    else if (error == CL_INVALID_DEVICE) {
        cerr << "Error in buildProgram (CL_INVALID_DEVICE)." << endl;
    }
    else if (error == CL_INVALID_BINARY) {
        cerr << "Error in buildProgram (CL_INVALID_BINARY)." << endl;
    }
    else if (error == CL_INVALID_BUILD_OPTIONS) {
        cerr << "Error in buildProgram (CL_INVALID_BUILD_OPTIONS)." << endl;
    }
    else if (error == CL_INVALID_OPERATION) {
        cerr << "Error in buildProgram (CL_INVALID_OPERATION)." << endl;
    }
    else if (error == CL_COMPILER_NOT_AVAILABLE) {
        cerr << "Error in buildProgram (CL_COMPILER_NOT_AVAILABLE)." << endl;
    }
    else if (error == CL_BUILD_PROGRAM_FAILURE) {
        cerr << "Error in buildProgram (CL_BUILD_PROGRAM_FAILURE)." << endl;
    }
    else if (error == CL_INVALID_OPERATION) {
        cerr << "Error in buildProgram (CL_INVALID_OPERATION)." << endl;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in buildProgram (CL_OUT_OF_HOST_MEMORY)." << endl;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in buildProgram. Error is not specified!" << endl;
    }

    return program;
}
void OpenCLLayerCreator::enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data) {
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

OpenCLLayer* OpenCLLayerCreator::createReluLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_device_id deviceId = openCLEnvironment->getDeviceId();
    cl_context context = openCLEnvironment->getContext();
    //cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();

    cl_program program = createProgram(context, deviceId, dirReluKernel);

    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * (size_t)sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * (size_t)sizeof(float));

    cl_int3 inputDim = { outputMaps, outputHeight, outputWidth};

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), (void*)&memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), (void*)&memOutputs);

    setKernelArg(feedforwardKernel, 2, sizeof(cl_int3), &inputDim);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);


    //error comp kernel
    cl_kernel errorCompKernel = createKernel(program, "errorComp");

    cl_mem memInputErrors = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));
    cl_mem memOutputErrors = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));

    setKernelArg(errorCompKernel, 0, sizeof(cl_mem), &memInputErrors);
    setKernelArg(errorCompKernel, 1, sizeof(cl_mem), &memOutputErrors);
    setKernelArg(errorCompKernel, 2, sizeof(cl_mem), &memInputs);
    setKernelArg(errorCompKernel, 3, sizeof(cl_int3), &inputDim);

    openCLLayer->setErrorCompKernel(errorCompKernel);
    openCLLayer->setMemErrorInputs(memInputErrors);
    openCLLayer->setMemErrorOutputs(memOutputErrors);

    return openCLLayer;
}
OpenCLLayer* OpenCLLayerCreator::createPadLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int padHeight, int padWidth) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_device_id deviceId = openCLEnvironment->getDeviceId();
    cl_context context = openCLEnvironment->getContext();
    cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();

    cl_program program = createProgram(context, deviceId, dirPadKernel);

    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * ((size_t)inputHeight+ (size_t)2*padHeight) * ((size_t)inputWidth+ (size_t)2*padWidth) * sizeof(float));
    
    cl_int3 inputDim = {inputMaps, inputHeight, inputWidth};
    cl_int2 padDim = {padHeight, padWidth};

    setZeros(memOutputs, commandQueue, (size_t)batchSize * inputMaps * ((size_t)inputHeight + (size_t)2 * padHeight) * ((size_t)inputWidth + (size_t)2 * padWidth));

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), (void*)&memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), (void*)&memOutputs);

    setKernelArg(feedforwardKernel, 2, sizeof(cl_int3), &inputDim);
    setKernelArg(feedforwardKernel, 3, sizeof(cl_int2), &padDim);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);

    //errorComp kernel
    cl_kernel errorCompKernel = createKernel(program, "errorComp");

    cl_mem memErrorInputs=createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memErrorOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * ((size_t)inputHeight + (size_t)2 * padHeight) * ((size_t)inputWidth + (size_t)2 * padWidth) * sizeof(float));

    setKernelArg(errorCompKernel, 0, sizeof(cl_mem), &memErrorInputs);
    setKernelArg(errorCompKernel, 1, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(errorCompKernel, 2, sizeof(cl_mem), &memInputs);
    
    setKernelArg(errorCompKernel, 3, sizeof(cl_int3), &inputDim);
    setKernelArg(errorCompKernel, 4, sizeof(cl_int2), &padDim);
    
    openCLLayer->setErrorCompKernel(errorCompKernel);
    openCLLayer->setMemErrorInputs(memErrorInputs);
    openCLLayer->setMemErrorOutputs(memErrorOutputs);

    return openCLLayer;
}
OpenCLLayer* OpenCLLayerCreator::createMaxPoolLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputHeight, int outputWidth, int poolHeight, int poolWidth, int strideHeight, int strideWidth) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_device_id deviceId = openCLEnvironment->getDeviceId();
    cl_context context = openCLEnvironment->getContext();
    //cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();

    cl_program program = createProgram(context, deviceId, dirMaxPoolKernel);

    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    int outputMaps = inputMaps;

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));
    
    cl_int3 inputDim = {inputMaps, inputHeight, inputWidth};
    cl_int3 outputDim = {outputMaps, outputHeight, outputWidth};
    cl_int2 poolDim = {poolHeight, poolWidth};
    cl_int2 strideDim = {strideHeight, strideWidth};

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), &memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), &memOutputs);

    setKernelArg(feedforwardKernel, 2, sizeof(cl_int3), &inputDim);
    setKernelArg(feedforwardKernel, 3, sizeof(cl_int3), &outputDim);
    setKernelArg(feedforwardKernel, 4, sizeof(cl_int2), &poolDim);
    setKernelArg(feedforwardKernel, 5, sizeof(cl_int2), &strideDim);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);

    //errorComp kernel
    cl_kernel errorCompKernel = createKernel(program, "errorComp");

    cl_mem memErrorInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memErrorOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * outputHeight * outputWidth * sizeof(float));

    clSetKernelArg(errorCompKernel, 0, sizeof(cl_mem), &memErrorInputs);
    clSetKernelArg(errorCompKernel, 1, sizeof(cl_mem), &memErrorOutputs);
    clSetKernelArg(errorCompKernel, 2, sizeof(cl_mem), &memInputs);
    clSetKernelArg(errorCompKernel, 3, sizeof(cl_mem), &memOutputs);
    clSetKernelArg(errorCompKernel, 4, sizeof(cl_int3), &inputDim);
    clSetKernelArg(errorCompKernel, 5, sizeof(cl_int3), &outputDim);
    clSetKernelArg(errorCompKernel, 6, sizeof(cl_int2), &poolDim);
    clSetKernelArg(errorCompKernel, 7, sizeof(cl_int2), &strideDim);

    openCLLayer->setMemErrorInputs(memErrorInputs);
    openCLLayer->setMemErrorOutputs(memErrorOutputs);
    openCLLayer->setErrorCompKernel(errorCompKernel);

    return openCLLayer;
}
OpenCLLayer* OpenCLLayerCreator::createSoftmaxLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_device_id deviceId = openCLEnvironment->getDeviceId();
    cl_context context = openCLEnvironment->getContext();
    //cl_command_queue commandQueue = openCLEnvironment->getCommandQueue();

    cl_program program = createProgram(context, deviceId, dirSoftmaxKernel);

    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * (size_t)sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * (size_t)sizeof(float));

    cl_int3 outputDim = {outputMaps, outputHeight, outputWidth};

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), (void*)&memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), (void*)&memOutputs);

    setKernelArg(feedforwardKernel, 2, sizeof(cl_int3), &outputDim);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);

    //errorComp kernel
    cl_kernel errorCompKernel = createKernel(program,"errorComp");

    cl_mem memErrorInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));
    cl_mem memErrorOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));

    setKernelArg(errorCompKernel, 0, sizeof(cl_mem), &memErrorInputs);
    setKernelArg(errorCompKernel, 1, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(errorCompKernel, 2, sizeof(cl_mem), &memInputs);

    setKernelArg(errorCompKernel, 3, sizeof(cl_int3), &outputDim);

    openCLLayer->setMemErrorInputs(memErrorInputs);
    openCLLayer->setMemErrorOutputs(memErrorOutputs);
    openCLLayer->setErrorCompKernel(errorCompKernel);

    return openCLLayer;
}
OpenCLLayer* OpenCLLayerCreator::createConvLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputMaps, int outputHeight, int outputWidth, int kernelHeight, int kernelWidth, int strideHeight, int strideWidth) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_context context = openCLEnvironment->getContext();
    cl_device_id device = openCLEnvironment->getDeviceId();

    cl_program program = createProgram(context, device, dirConvKernel);
    
    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));
    
    cl_mem memWeights = createBuffer(context, CL_MEM_READ_WRITE, (size_t)outputMaps * inputMaps * kernelHeight * kernelWidth * sizeof(float));
    cl_mem memBiases = createBuffer(context, CL_MEM_READ_WRITE, (size_t)outputMaps * sizeof(float));

    cl_int3 inputDim = { inputMaps, inputHeight, inputWidth };
    cl_int3 outputDim = { outputMaps, outputHeight, outputWidth };
    cl_int2 kernelDim = { kernelHeight, kernelWidth};
    cl_int2 strideDim = { strideHeight, strideWidth };

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), &memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), &memOutputs);
    setKernelArg(feedforwardKernel, 2, sizeof(cl_mem), &memWeights);
    setKernelArg(feedforwardKernel, 3, sizeof(cl_mem), &memBiases);
    setKernelArg(feedforwardKernel, 4, sizeof(cl_int3), &inputDim);
    setKernelArg(feedforwardKernel, 5, sizeof(cl_int3), &outputDim);
    setKernelArg(feedforwardKernel, 6, sizeof(cl_int2), &kernelDim);
    setKernelArg(feedforwardKernel, 7, sizeof(cl_int2), &strideDim);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setMemWeights(memWeights);
    openCLLayer->setMemBiases(memBiases);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);
    
    //errorComp kernel
    cl_kernel kernelErrorComp = createKernel(program, "errorComp");

    cl_mem memErrorInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memErrorOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputMaps * outputHeight * outputWidth * sizeof(float));

    setKernelArg(kernelErrorComp, 0, sizeof(cl_mem), &memErrorInputs);
    setKernelArg(kernelErrorComp, 1, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(kernelErrorComp, 2, sizeof(cl_mem), &memInputs);
    setKernelArg(kernelErrorComp, 3, sizeof(cl_mem), &memWeights);
    setKernelArg(kernelErrorComp, 4, sizeof(cl_int3), &inputDim);
    setKernelArg(kernelErrorComp, 5, sizeof(cl_int3), &outputDim);
    setKernelArg(kernelErrorComp, 6, sizeof(cl_int2), &kernelDim);
    setKernelArg(kernelErrorComp, 7, sizeof(cl_int2), &strideDim);

    openCLLayer->setMemErrorInputs(memErrorInputs);
    openCLLayer->setMemErrorOutputs(memErrorOutputs);
    openCLLayer->setErrorCompKernel(kernelErrorComp);
    
    //updateWeights kernel
    cl_kernel kernelUpdateWeights = createKernel(program, "weightsUpdate");

    //cl_mem memLearningRate = createBuffer(context, CL_MEM_READ_ONLY, sizeof(float));

    //setKernelArg(kernelUpdateWeights, 0, sizeof(cl_mem), &memLearningRate);
    setKernelArg(kernelUpdateWeights, 1, sizeof(cl_mem), &memInputs);
    setKernelArg(kernelUpdateWeights, 2, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(kernelUpdateWeights, 3, sizeof(cl_mem), &memWeights);
    setKernelArg(kernelUpdateWeights, 4, sizeof(cl_mem), &memBiases);
    setKernelArg(kernelUpdateWeights, 5, sizeof(cl_int), &batchSize);
    setKernelArg(kernelUpdateWeights, 6, sizeof(cl_int3), &outputDim);
    setKernelArg(kernelUpdateWeights, 7, sizeof(cl_int3), &inputDim);
    setKernelArg(kernelUpdateWeights, 8, sizeof(cl_int2), &kernelDim);
    setKernelArg(kernelUpdateWeights, 9, sizeof(cl_int2), &strideDim);

    openCLLayer->setWeightsUpdateKernel(kernelUpdateWeights);
    
    return openCLLayer;
}
OpenCLLayer* OpenCLLayerCreator::createDenseLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputNeurons) {
    OpenCLLayer* openCLLayer = new OpenCLLayer();

    cl_context context = openCLEnvironment->getContext();
    cl_device_id device = openCLEnvironment->getDeviceId();

    cl_program program = createProgram(context, device, dirDenseKernel);

    //feedforward kernel
    cl_kernel feedforwardKernel = createKernel(program, "feedforward");

    cl_mem memInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputNeurons * sizeof(float));
   
    cl_mem memWeights = createBuffer(context, CL_MEM_READ_WRITE, (size_t)inputMaps * inputHeight * inputWidth * outputNeurons * sizeof(float));
    cl_mem memBiases = createBuffer(context, CL_MEM_READ_WRITE, (size_t)outputNeurons * sizeof(float));

    cl_int3 inputDim = {inputMaps, inputHeight, inputWidth};
    cl_int outputNeu = outputNeurons;

    setKernelArg(feedforwardKernel, 0, sizeof(cl_mem), &memInputs);
    setKernelArg(feedforwardKernel, 1, sizeof(cl_mem), &memOutputs);
    setKernelArg(feedforwardKernel, 2, sizeof(cl_mem), &memWeights);
    setKernelArg(feedforwardKernel, 3, sizeof(cl_mem), &memBiases);
    setKernelArg(feedforwardKernel, 4, sizeof(cl_int3), &inputDim);
    setKernelArg(feedforwardKernel, 5, sizeof(cl_int), &outputNeu);

    openCLLayer->setMemInputs(memInputs);
    openCLLayer->setMemOutputs(memOutputs);
    openCLLayer->setMemWeights(memWeights);
    openCLLayer->setMemBiases(memBiases);
    openCLLayer->setProgram(program);
    openCLLayer->setFeedforwardKernel(feedforwardKernel);
    
    //errorComp kernel
    cl_kernel kernelErrorComp = createKernel(program, "errorComp");

    cl_mem memErrorInputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * inputMaps * inputHeight * inputWidth * sizeof(float));
    cl_mem memErrorOutputs = createBuffer(context, CL_MEM_READ_WRITE, (size_t)batchSize * outputNeurons * sizeof(float));

    setKernelArg(kernelErrorComp, 0, sizeof(cl_mem), &memErrorInputs);
    setKernelArg(kernelErrorComp, 1, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(kernelErrorComp, 2, sizeof(cl_mem), &memInputs);
    setKernelArg(kernelErrorComp, 3, sizeof(cl_mem), &memWeights);
    setKernelArg(kernelErrorComp, 4, sizeof(cl_int3), &inputDim);
    setKernelArg(kernelErrorComp, 5, sizeof(cl_int), &outputNeurons);

    openCLLayer->setMemErrorInputs(memErrorInputs);
    openCLLayer->setMemErrorOutputs(memErrorOutputs);
    openCLLayer->setErrorCompKernel(kernelErrorComp);
    
    
    //updateWeights kernel
    cl_kernel kernelUpdateWeights = createKernel(program, "weightsUpdate");

    //setKernelArg(kernelUpdateWeights, 0, sizeof(cl_mem), &memLearningRate);
    setKernelArg(kernelUpdateWeights, 1, sizeof(cl_mem), &memInputs);
    setKernelArg(kernelUpdateWeights, 2, sizeof(cl_mem), &memErrorOutputs);
    setKernelArg(kernelUpdateWeights, 3, sizeof(cl_mem), &memWeights);
    setKernelArg(kernelUpdateWeights, 4, sizeof(cl_mem), &memBiases);
    setKernelArg(kernelUpdateWeights, 5, sizeof(cl_int), &batchSize);
    setKernelArg(kernelUpdateWeights, 6, sizeof(cl_int), &outputNeurons);
    setKernelArg(kernelUpdateWeights, 7, sizeof(cl_int3), &inputDim);

    openCLLayer->setWeightsUpdateKernel(kernelUpdateWeights);
    
    return openCLLayer;
}

//setters
void OpenCLLayerCreator::setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue) {
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
void OpenCLLayerCreator::setZeros(cl_mem mem, cl_command_queue commandQueue, size_t size) {
    float* zeros = (float*)malloc(sizeof(float) * size);

    if (zeros) {
        for (unsigned int i = 0; i < size; i++) {
            zeros[i] = ((float) (0));
        }

        enqueueWriteBuffer(commandQueue, mem, size * sizeof(float), zeros);

        free(zeros);
    }
}
