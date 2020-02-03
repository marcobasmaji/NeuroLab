/**
*	@brief	Every object of this class represents a layer of the neural net and holds all necessary OpenCL data for this layer. Also, it holds the functionality for executing the forward and backward pass for this layer. To create this class use the OpenCLLayerCreator.
*/

#pragma once

#include "CL/cl.h"

#include "OpenCLEnvironment.hpp"

class OpenCLLayer {
private:

	cl_mem memInputs = nullptr;			/**This attribute holds the buffer on the hardware device for the input data of the layer this class represents.*/
	cl_mem memOutputs = nullptr;		/**This attribute holds the buffer on the hardware device for the output data of the layer this class represents.*/
	cl_mem memBiases = nullptr;			/**This attribute holds the buffer on the hardware device for the biases of this layer. If the layer, this class represents does not have biases, i.e. the pooling layer, this attribute stays uninitialized.*/
	cl_mem memWeights = nullptr;		/**This attribute holds the buffer on the hardware device for the weights of this layer. If the layer, this class represents does not have weights, i.e. the pooling layer, this attribute stays uninitialized.*/
	cl_mem memErrorInputs = nullptr;	/**This attribute holds the buffer on the hardware device for the errors of the input neurons in this layer.*/
	cl_mem memErrorOutputs = nullptr;	/**This attribute holds the buffer on the hardware device for the errors of the output neurons of in this layer.*/

	cl_program program = nullptr;				/**This attribute holds the OpenCL program of this layer.*/
	cl_kernel kernelFeedforward = nullptr;		/**This attribute holds the feedforward kernel object. After executing this kernel performs the forward pass which is required for classification and training.*/
	cl_kernel kernelErrorComp = nullptr;		/**This attribute holds the kernel object that is responsible for calculating the gradients (errors). It is necessary for training and updating the weights and biases. For classification, this kernel object is not used. Before the weights can be updated this kernel has to be called.*/
	cl_kernel kernelWeightsUpdate = nullptr;	/**This attribute holds the kernel that is responsible for updating the parameters like weights and biases. It just has to be called during training and after executing the kernel kernelBackward. Also, this kernel is initialized only for trainable layers with weights and biases.*/

	ReleaseCLObjectsManager* releaseCLObjectsManager=nullptr;	/**This attribute holds a pointer to an object of the ReleaseCLObjectsManager class.*/

/**
*	@brief					This function executes a kernel. It just calls clEnqueueNDRangeKernel and cerr's eventual errors.
*	@param commandQueue		The command queue this execute command should be put in.
*	@param kernel			The kernel that should be executed.
*	@param workDim			The number of working dimensions in which the kernel is executed in parallel. This value has to be >= one and <= three.
*	@param globalWorkSize	This attribute has to be an array with size equals to workDim. It describes how often the kernel should be executed in parallel in each of the possible three dimensions. It sets the global work size. Because the local work size is set equals to NULL OpenCL decides on its own how the work group size is set.
*/
	void executeKernel(cl_command_queue commandQueue, cl_kernel kernel, cl_uint workDim, const size_t* globalWorkSize);
	
/**
*	@brief			This function just calls the OpenCL function clSetKernelArg and sets an argument of the kernel.
*	@param kernel	The kernel in which the argument should be set.
*	@param index	The index this argument has in the overhanded kernel.
*	@param argSize	The size of the overhanded argValue in bytes.
*	@param argValue	The value the kernel argument set be equals to.
*/
	void setKernelArg(cl_kernel kernel, cl_uint index, size_t argSize, const void* argValue);

/**
*	@brief				This function loads data from the overhanded mem object. It just calls the OpenCL function clEnqueueReadBuffer and cerr's possible errors. After completion, it returns the data. This function is blocking and only continues if the data has been read or copied.
*	@param commandQueue	The OpenCL command queue the command should be put in.
*	@param size			The length of the requested data.
*	@param mem			The mem object of the requested data.
*	@return				The requested data read from the hardware device.
*/
	void* enqueueReadBuffer(cl_command_queue commandQueue, size_t size, cl_mem mem);
	
/**
*	@brief				This function writes data to a buffer of a hardware device. It just checks the validity of the overhanded attributes, calls clEnqueueWriteBuffer and cerr's possible errors. It is blocking and only continues if the data has been read or copied.
*	@param commandQueue	The OpenCL command queue the command should be put in.
*	@param mem			The memory object where the data should be written to.
*	@param size			The length of the data that should be written to the device.
*	@param data			The data that should be written to the device.
*/
	void enqueueWriteBuffer(cl_command_queue commandQueue, cl_mem mem, size_t size, void* data);

/**
*	@brief	This function releases all resources initialized (attributes, data, and buffers they point to) in this object. It has to be called at the end of the lifetime of this object because afterward, no calculations in this class will function properly anymore. 
*/
	void releaseResources();

public:
/**
*	@brief	This constructor just initializes the releaseCLObjectsManager attribute with an object of its corresponding class.
*/
	OpenCLLayer();
	
/**
*	@brief	This destructor just calls the releaseResources function before destroying the object and deletes the releaseCLObjectsManager object. 
*/
	~OpenCLLayer();

/**
*	@brief						This function performs the forward pass on the overhanded hardware type. For the first layer the input data, e.g. the image has to be set via calling setInputs. In case this layer is a hidden one, it takes the output of the layer before. But before this, the setPreviousLayer function has to be called.
*	@param openclEnvironment	The OpenCLEnvironment that represents the hardware on which the forward pass should be calculated.
*	@param batchSize			The batch size describes how many images should be processed in parallel. It has to fit the batch size of the previous layer and to the number of set input images.
*	@param outputMaps			The number of output maps of this layer. In the case of a dense layer, this value is the number of output neurons.     
*/
	void computeForward(OpenCLEnvironment* openCLEnvironment, size_t batchSize, size_t outputMaps);
	
/**
*	@brief						This function is just for training important. It calculates the errors (the gradients) at the backpass. The training part is split into this function and computeWeightsUpdate because they allow different parallel optimization methods. To train the network first computeForward has to be called for every layer. After that, this function should be called beginning from the last layer to the first one. In the end, computeWeightsUpdate can be called in any direction either from the first layer or the other side.
*	@param openclEnvironment	The OpenCLEnvironment that represents the hardware on which the errors should be calculated.
*	@param batchSize			The batch size describes how many images should be processed in parallel. It has to fit the batch size of the previous layer and the number of input images.
*/
	void computeErrorComp(OpenCLEnvironment* openCLEnvironment, size_t batchSize);
	
/**
*	@brief						This function is just for training important. It updates the weights and biases. The training part is split into this function and computeErrorComp because they allow different parallel optimization methods. To train the network first computeForward has to be called for every layer. After that, computeErrorComp should be called beginning from the last layer to the first one. In the end, this method can be called in any direction either from the first layer or the last one.
*	@param openclEnvironment	The OpenCLEnvironment that represents the hardware on which the new weights and biases should be calculated.
*	@param outputMaps			The number of output maps of this layer. In the case of a dense layer, this value is the number of output neurons.
*/
	void computeWeightsUpdate(OpenCLEnvironment* openCLEnvironment, size_t outputMaps);

	//setters
/**
*	@brief				This function is a setter for the memInputs attribute. It checks the validity of the overhanded attribute, cerr's eventual errors and sets it.
*	@param memInputs	The buffer for the input data on the hardware device for this layer.
*/
	void setMemInputs(cl_mem memInputs);
	
/**
*	@brief				This function is a setter for the memOutputs attribute, cerr's eventual errors and sets it.
*	@param memOutputs	The buffer for the output data on the hardware device for this layer.
*/
	void setMemOutputs(cl_mem memOutputs);
	
/**
*	@brief				This function sets the memBiases attribute and cerr's eventual errors. It can only be set in layers that has biases.
*	@param memBiases	The buffer for the biases on the hardware device for this layer.
*/
	void setMemBiases(cl_mem memBiases);
	
/**
*	@brief				This function sets the memWeights attribute and cerr's eventual errors. It can only be set if this layer has weights.
*	@param memWeights	The buffer for the weights on the hardware device for this layer.
*/
	void setMemWeights(cl_mem memWeights);
	
/**
*	@brief				This function sets the memErrorInputs attribute and cerr's eventual errors.
*	@param memErrors	The buffer for the gradients (errors) on the hardware device for this layer.
*/
	void setMemErrorInputs(cl_mem memErrorInputs);
	
/**
*	@brief				This function sets the memErrorOutputs attribute and cerr's eventual errors.
*	@param memErrors	The buffer for the gradients (errors) on the hardware device for this layer.
*/
	void setMemErrorOutputs(cl_mem memErrorOutputs);


/**
*	@brief						This function sets the kernelFeedforward attribute and cerr's eventual errors.
*	@param kernelFeedforward	The kernel object for the feedforward kernel.
*/
	void setFeedforwardKernel(cl_kernel kernelFeedforward);
	
/**
*	@brief					This function sets the kernelErrorComp attribute and cerr's eventual errors.
*	@param kernelErrorComp	The kernel object for the backward kernel.
*/
	void setErrorCompKernel(cl_kernel kernelErrorComp);
	
/**
*	@brief						This function sets the kernelWeightsUpdate attribute and cerr's eventual errors. If the layer can not perform a weights update, like the pooling layer, this function must not be called.
*	@param kernelWeightsUpdate	The kernel object for the weights update kernel.
*/
	void setWeightsUpdateKernel(cl_kernel kernelWeightsUpdate);

/**
*	@brief			This function sets the program attribute and cerr's eventual errors.
*	@param program	The OpenCL program object.
*/
	void setProgram(cl_program program);
	
/**
*	@brief						This function sets the output neurons of the i layer to the input neurons of the i-1 layer (it sets the memInputs attribute and memOutputs attribute equals and sets the memErrorInputs attribute and memErrorOutputs attribute equals). It has to be called just once after creating the i and i-1 layer.
*	@param previousOpenCLLayer	The OpenCLLayer object, that stands for the previous layer of the layer this object stands for.
*/
	void setPreviousOpenCLLayer(OpenCLLayer* previousOpenCLLayer);

/**
*	@brief						This function loads the overhanded data to the memInputs buffer. It has to be called before using computeForward and just has to be called for the first layer to set its inputs. It is blocking and only continues if the data has been read and copied.
*	@param openclEnvironment	The OpenCL environment which represents the hardware on that the input data of this layer should be loaded to.
*	@param input				The input data of this layer in form as a pointer that points to an array.
*	@param length				The length of the input data array.
*/
	void setInputs(OpenCLEnvironment* openCLEnvironment, float* input, int length);
	
/**
*	@brief						This function loads the overhanded weights to the memWeights buffer. In case this layer does not have weights i.e. the pooling layer, this function must not be called.
*	@param openclEnvironment	The OpenCL environment which represents the hardware on that the weights of this layer should be loaded.
*	@param weights				The weights as an array in form of a pointer to this array.
*	@param length				The length of the weights array.
*/
	void setWeights(OpenCLEnvironment* openCLEnvironment, float* weights, int length);
	
/**
*	@brief						This function loads the overhanded biases to the memBiases buffer. In case this layer does not have biases i.e. the pooling layer, this function must not be called.
*	@param openCLEnvironment	The OpenCLEnvironment that represents the hardware device the biases should be written to.
*	@param biases				The biases that should be written to the device.
*	@param length				The length of the biases array.
*/
	void setBiases(OpenCLEnvironment* openCLEnvironment, float* biases, int length);
	
/**
*	@brief						This function loads the overhanded biases to the memErrorOutputs buffer. It have to be only called before calling the computeErrorComp function for the last layer.
*	@param openCLEnvironment	The OpenCLEnvironment that represents the hardware device the errors should be written to.
*	@param outputErrors			The errors that should be written to the device.
*	@param length				The length of the error array.
*/
	void setOutputErrors(OpenCLEnvironment* openCLEnvironment, float* outputErrors, int length);
	
/**
*	@brief						
*	@param learningRate	
*/
	void setLearningRate(float learningRate);

	//getters
/**
*	@brief	This function is a getter for the memErrorInputs attribute.
*	@return	The memErrorInputs attribute.
*/
	cl_mem getMemErrorInputs();
	
/**
*	@brief	This function is a getter for the memErrorOutputs attribute.
*	@return	The memErrorOutputs attribute.
*/
	cl_mem getMemErrorOutputs();
	
/**
*	@brief	This function is a getter for the memOutputs attribute.
*	@return	The memOutputs attribute.
*/
	cl_mem getMemOutputs();
	
/**
*	@brief	This function is a getter for the memInputs attribute.
*	@return	The memInputs attribute.
*/
	cl_mem getMemInputs();

/**
*	@brief	This function is a getter for the kernelErrorComp attribute.
*	@return	The kernelErrorComp attribute.
*/
	cl_kernel getKernelErrorComp();
	
/**
*	@brief	This function is a getter for the kernelWeightsUpdate attribute.
*	@return	The kernelWeightsUpdate attribute.
*/
	cl_kernel getKernelUpdateWeights();
	
/**
*	@brief					This function loads the overhanded weights to the memWeights buffer. In case this layer does not have weights i.e. the pooling layer, this function must not be called.
*	@param openclEnvironment		The OpenCL environment which represents the hardware on that the weights of this layer should be loaded.
*	@param length				The length of the weights array.
*	@param weights				The array in which the weights should be saved.
*/
	void getWeights(OpenCLEnvironment* openCLEnvironment, int length, float* weights);

/**
*	@brief						This function returns the calculated errors (gradients) of the output neurons of this layer. It is blocking and only continues if the data has been read and copied.
*	@param openclEnvironment	The OpenCLEnvironment that stands for the hardware this layer is initialized on and the data is stored.
*	@param batchSize			The batch size of the output data.
*	@param outputMaps			The output maps of the output layer. In the case of a dense layer, this attribute is the number of output neurons.
*	@param outputHeight			The output height of the output layer. In the case of a dense layer, this attribute is 1.
*	@param outputWidth			The output width of the output layer. In the case of a dense layer, this attribute is 1.
*	@param arrayLength			This attribute is set equals to the length of the return array. Its memory has to be reserved by the caller.
*	@return						The error (gradients) data of the output neurons of this layer.
*/
	float* getErrors(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength);
	
/**
*	@brief						This function reads the outputs of this layer. It is blocking and only continues if the data has been read and copied.
*	@param openclEnvironment	The OpenCLEnvironment that stands for the hardware this layer is initialized on and the data is stored.
*	@param batchSize			The batch size of the output data.
*	@param outputMaps			The output maps of the output layer. In the case of a dense layer, this attribute is the number of output neurons.
*	@param outputHeight			The output height of the output layer. In the case of a dense layer, this attribute is 1.
*	@param outputWidth			The output width of the output layer. In the case of a dense layer, this attribute is 1.
*	@param arrayLength			This attribute is set equals to the length of the return array. Its memory has to be reserved by the caller.
*	@return						The output data of the output layer.
*/
	float* getOutputs(OpenCLEnvironment* openCLEnvironment, int batchSize, int outputMaps, int outputHeight, int outputWidth, int* arrayLength);
};
