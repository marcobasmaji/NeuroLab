/**
*	@brief	This class just holds functions to release OpenCL ressources. It is used by the OpenCLLayer and the OpenCLEnvironment. The only purpose of this class is to reduce redundancy and deserve more convenience for the programmer.
*/
#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

 #include "CL/cl.h"

class ReleaseCLObjectsManager {
public:
	/**
	*	@brief 			This method just releases the overhanded cl_device_id. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_device_id, that should be released.
	*/
	void releaseDeviceId(cl_device_id deviceId);
	/**
	*	@brief 			This method just releases the overhanded cl_context. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_context, that should be released.
	*/
	void releaseContext(cl_context context);
	/**
	*	@brief 			This method just releases the overhanded cl_context. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_command_queue, that should be released.
	*/
	void releaseCommandQueue(cl_command_queue commandQueue);

	/**
	*	@brief 			This method just releases the overhanded cl_context. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_mem, that should be released.
	*/
	void releaseMemObject(cl_mem mem);
	/**
	*	@brief 			This method just releases the overhanded cl_context. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_kernel, that should be released.
	*/
	void releaseKernel(cl_kernel kernel);
	/**
	*	@brief 			This method just releases the overhanded cl_context. Also it checks for eventual errors and cerr's them.
	*	@param deviceID The cl_program, that should be released.
	*/
	void releaseProgram(cl_program program);
};
