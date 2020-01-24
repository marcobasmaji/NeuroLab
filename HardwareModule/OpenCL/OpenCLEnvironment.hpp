/**
*	@brief Each object of this class represents a hardware device, like the FPGA, GPU or CPU. It is a container that holds all relevant OpenCL data for this device. To create an object of this class use the OpenCLEnvironmentCreator class.
*/

#pragma once

#include "../../Tools/opencl/include/cl.h"
#include "HardwareEnvironment.hpp"
#include "ReleaseCLObjectsManager.hpp"

class OpenCLEnvironment : HardwareEnvironment {

public:
	/**
	*	@brief	This constructor initiliazes the releaseCLObjectsManager attribute with a new object of its class.
	*/
	OpenCLEnvironment();
	/**
	*	@brief	This destructor have to be called at the end via delete to release all the OpenCl ressources. Also it deletes the releaseCLObjectsManager attribute.
	*/
	~OpenCLEnvironment();

	//setters
	/**
	*	@brief				This method is the setter for the platformId attribute of the hardware, this object represents.
	*	@param platformId	The cl_platform_id of the hardware, this object represents.
	*/
	void setPlatformId(cl_platform_id platformId);
	/**
	*	@brief			This method is the setter for the deviceID attribute of the hardware, this object represents. If the deviceId of this class have already been set, it releases it and sets it equals the overhanded one.
	*	@param deviceId	The cl_device_id of the hardware, this object represents.
	*/
	void setDeviceId(cl_device_id deviceId);
	/**
	*	@brief			This method is the setter for the context attribute of the hardware, this object represents. If the context of this class have already been set, it releases it and sets it equals the overhanded one.
	*	@param deviceId	The cl_context of the hardware, this object represents.
	*/
	void setContext(cl_context context);
	/**
	*	@brief			This method is the setter for the commandQueue attribute of the hardware, this object represents. If the commandQueue of this class have already been set, it releases it and sets it equals the overhanded one.
	*	@param deviceId	The cl_command_queue of the hardware, this object represents.
	*/
	void setCommandQueue(cl_command_queue commandQueue);

	//getters
	/**
	*	@brief	This method is the getter for the platformId attribute.
	*	@return	The platformId attribute.
	*/
	cl_platform_id getPlatformId();
	/**
	*	@brief	This method is the getter for the deviceId attribute.
	*	@return	The deviceId attribute.
	*/
	cl_device_id getDeviceId();
	/**
	*	@brief	This method is the getter for the context attribute.
	*	@return	The context attribute.
	*/
	cl_context getContext();
	/**
	*	@brief	This method is the getter for the commandQueue attribute.
	*	@return	The commandQueue attribute.
	*/
	cl_command_queue getCommandQueue();

private:
	/**
	*	@brief	This attribute holds the OpenCL platform id. Only one platform can be selected per hardware.
	*/
	cl_platform_id platformId=nullptr;
	/**
	*	@brief	This attribute holds the OpenCL device id for the selected hardware. Only one device can be selected per OpenCLEnvironment object.
	*/
	cl_device_id deviceId = nullptr;
	/**
	*	@brief	This attribute holds the OpenCL context that combines device id and platform id.
	*/
	cl_context context = nullptr;
	/**
	*	@brief	This attribute holds the OpenCL command queue for all the requests, i.e. loading data onto the device buffer or executing a kernel on it.
	*/
	cl_command_queue commandQueue = nullptr;

	/**
	*	@brief	This attribute holds a pointer to an object of the ReleaseCLObjectsManager class. It is responsible for releasing OpenCL ressources.
	*/
	ReleaseCLObjectsManager* releaseCLObjectsManager=nullptr;

	/**
	*	@brief	This method releases all the reserved OpenCL ressources. It is called at the end by the deconstructor before deleting this object.
	*/
	void releaseResources();
};
