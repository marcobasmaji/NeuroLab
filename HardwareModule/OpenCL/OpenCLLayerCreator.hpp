/**
*	@brief	This class is just a creator class that creates an OpenCLLayer object and initializes all dependent attributes. It only has to be created once at the very beginning. During the creation process for every layer of the network, the proper function of this class has to be called. In this function, all the arguments will be set if possible. Therefore the batch size will be fixed. Only attributes like the inputs of the first layer and the expected outputs of the last layer have to be loaded onto the device every passage. Then it returns a pointer to an OpenCLLayer class that can be stored in that layer and never has to be altered afterward.
*/

#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <string>
#include "CL/cl.h"

#include "OpenCLLayer.hpp"
#include "OpenCLEnvironment.hpp"

using namespace std;

class OpenCLLayerCreator {
private:
    const char* dirConvKernel = "kernels/Conv.cl";			/**This attribute holds the relative path to the convolutional layer kernels.*/
    const char* dirMaxPoolKernel = "kernels/MaxPool.cl";	/**This attribute holds the relative path to the max pooling layer kernels.*/
    const char* dirDenseKernel = "kernels/Dense.cl";		/**This attribute holds the relative path to the dense layer kernels.*/
    const char* dirReluKernel = "kernels/Relu.cl";			/**This attribute holds the relative path to the relu layer kernels.*/
    const char* dirPadKernel = "kernels/Pad.cl";			/**This attribute holds the relative path to the padding layer kernels.*/
    const char* dirSoftmaxKernel = "kernels/Softmax.cl";	/**This attribute holds the relative path to the softmax layer kernels.*/

/**
*/
    void setZeros(cl_mem mem, cl_command_queue commandQueue, size_t size);

/**
*	@brief				This function just calls the OpenCL function clEnqueueWriteBuffer and passes data to the overhanded buffer object. Also, it cerr's eventual errors.
*	@param commandQueue	The commandQueue in which this command should be put in.
*	@param mem			The memory object where the data should be written to.
*	@param size			The size of data in bytes.
*	@param data			The data that should be written into the overhanded buffer.
*/
	void enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data);
    
/**
*	@brief			This creates a buffer on the hardware device specified by the context attribute, cerr's eventual errors and returns this buffer. 
*	@param context	The context that describes on which the buffer should be created.
*	@param flags	The flags that describes how the buffer should be like, i.e. read-only, write-only or both.
*	@param size		The size of the created buffer in bytes.
*	@return			The created buffer.
*/
	cl_mem createBuffer(cl_context context, cl_mem_flags flags, size_t size);

/**
*	@brief				This function creates a kernel. Therefore it takes the compiled program and takes the function name of the kernel. This is done by calling the OpenCL function clCreateKernel and afterward it cerr's eventual errors.
*	@param program		The compiled program in which the kernel is in.
*	@param functionName	The function name of the kernel.
*	@return				The cl_kernel object that points to that kernel.
*/  
    cl_kernel createKernel(cl_program program, const char* functionName);
    
/**
*	@brief				This function loads a kernel from a file, compiles it, builds it and returns a cl_program object. It checks the validity of the arguments. Then it calls loadFile to load the kernel from the given path. After loading it the kernel gets created with clCreateProgramWithSource and last, it gets built with clBuildProgram. During the whole process, this function checks for eventual errors and cerr's them.
*	@param context		The context for which the program should be created and compiled.
*	@param device		The device for which the program should be created and compiled.
*	@param dirKernel	The path to the kernel file.
+	@return				The created cl_program attribute. 
*/
	cl_program createProgram(cl_context context, cl_device_id device, const char* dirKernel);

/**
*	@brief				This function loads the file from the overhanded path and returns the content of it.
*	@param path			The path of the file that should be loaded.
*	@param sourceSize	This attribute is set by the function equals to the length of the content of the loaded file in bytes.
*	@return				The content of the loaded file.
*/
	string loadFile(const char *path);

    //setters
/**
*	@brief			This function sets an argument of the given OpenCL kernel via calling the OpenCL function clSetKernelArg. Afterward, it cerr's eventual errors.
*	@param kernel	The kernel on which the argument should be set.
*	@param index	The index of the argument that should be set.
*	@param argSize	The size in bytes of the argument.
*	@param argValue	The actual data that should be loaded to the device and set as the kernel function argument.
*/
    void setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue);

public:
/**
*	@brief						This function creates the OpenCLLayer object for a ReLU layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be equal for all layers.
*	@param outputMaps			The number of output maps (equals to the number of input maps) of this layer.
*	@param outputHeight			The height dimension of the output layer.
*	@param outputWidth			The width dimension of the output layer.
*	@return						The pointer to the created OpenCLLayer object that represents this ReLU layer and executes the OpenCL calculations.
*/
    OpenCLLayer* createReluLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth);
    
/**
*	@brief						This function creates the OpenCLLayer object for a padding layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be equal for all layers.
*	@param inputMaps			The number of output maps (equal to the number of input maps) of this layer.
*	@param inputHeight			The height dimension of the output layer.
*	@param inputWidth			The width dimension of the output layer.
*	@param padHeight			The vertical padding dimension (the output height will be inputHeight + 2 * padHeight).
*	@param padWidth				The horizontal padding dimension (the output width will be inputWidth + 2 * padWidth).
*	@return						The pointer to the created OpenCLLayer object that represents this padding layer and executes the OpenCL calculations.
*/
	OpenCLLayer* createPadLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int padHeight, int padWidth);
	
/**
*	@brief						This function creates the OpenCLLayer object for a convolutional layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be equal for all layers.
*	@param inputMaps			The number of input maps of this layer.
*	@param inputHeight			The vertical input dimension of this layer.
*	@param inputWidth			The horizontal input dimension of this layer.
*	@param outputMaps			The number of output maps of this layer.
*	@param outputHeight			The vertical output dimension of this layer.
*	@param outputWidth			The horizontal output dimension of this layer.
*	@param kernelHeight			The height of the kernel filter.
*	@param kernelWidth			The width of the kernel filter.
*	@param strideHeight			The vertical stride value of the convolution operation.
*	@param strideWidth			The horizontal stride value of the convolution operation.
*	@return						The pointer to the created OpenCLLayer object that represents this convolutional layer and executes the OpenCL calculations.
*/
    OpenCLLayer* createConvLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputMaps, int outputHeight, int outputWidth, int kernelHeight, int kernelWidth, int strideHeight, int strideWidth);

/**
*	@brief						This function creates the OpenCLLayer object for a max pooling layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be equal for all layers.
*	@param inputMaps			The number of input maps (equals to the number of output maps) of this layer.
*	@param inputHeight			The vertical input dimension of this layer. 
*	@param inputWidth			The horizontal input dimension of this layer.
*	@param outputHeight			The vertical output dimension of this layer.
*	@param outputWidth			The horizontal output dimension of this layer.
*	@param poolHeight			The height of the pooling filter.
*	@param poolWidth			The width of the pooling filter.
*	@param strideHeight			The vertical stride value of the pooling operation.
*	@param strideWidth			The horizontal stride value of the pooling operation.
*	@return						The pointer to the created OpenCLLayer object that represents this max pooling layer and executes the OpenCL calculations.
*/    
	OpenCLLayer* createMaxPoolLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputHeight, int outputWidth, int poolHeight, int poolWidth, int strideHeight, int strideWidth);
    
/**
*	@brief						This function creates the OpenCLLayer object for a dense layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be equal for all layers.
*	@param inputMaps			The number of input maps.
*	@param inputHeight			The vertical input dimension of this layer.
*	@param inputWidth			The horizontal input dimension of this layer.
*	@param outputNeurons		The number of output neurons. In memory, this dimension is modeled as the map dimension. The outputHeight and outputWidth dimension is set equal to 1.
*	@return						The pointer to the created OpenCLLayer object that represents this dense layer and executes the OpenCL calculations.
*/
	OpenCLLayer* createDenseLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int inputMaps, int inputHeight, int inputWidth, int outputNeurons);
	
/**
*	@brief						This function creates the OpenCLLayer object for a softmax layer and initializes its attributes.
*	@param openClEnvironment	The OpenCLEnvironment object that stands for the hardware on which this layer should be executable.
*	@param batchSize			The batch size that should be able to be calculated with this layer. This value has to be alike for all layers.
*	@param outputMaps			The number of output maps.
*	@param outputHeight			The output height of the layer.
*	@param outputWidth			The output width of this layer.
*	@return						The pointer to the created OpenCLLayer object that represents this softmax layer and executes the OpenCL calculations.
*/
    OpenCLLayer* createSoftmaxLayer(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth);
};

