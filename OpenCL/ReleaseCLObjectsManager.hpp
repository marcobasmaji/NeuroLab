//checked

#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include <CL/cl.h>

class ReleaseCLObjectsManager {
public:
	void releaseDeviceId(cl_device_id deviceId);
	void releaseContext(cl_context context);
	void releaseCommandQueue(cl_command_queue commandQueue);

	void releaseMemObject(cl_mem mem);
	void releaseKernel(cl_kernel kernel);
	void releaseProgram(cl_program program);
};
