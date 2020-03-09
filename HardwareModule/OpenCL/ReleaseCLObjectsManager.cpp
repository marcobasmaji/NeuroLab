//checked

#include "ReleaseCLObjectsManager.hpp"

#include <iostream>

using namespace std;

void ReleaseCLObjectsManager::releaseDeviceId(cl_device_id deviceId) {
	cl_int error = clReleaseDevice(deviceId);
	
	if (error == CL_INVALID_DEVICE) {
		cerr << "Error in releaseDeviceId (CL_INVALID_DEVICE)." << endl;
	}
	else if (error == CL_OUT_OF_RESOURCES) {
		cerr << "Error in releaseDeviceId (CL_OUT_OF_RESOURCES)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in releaseDeviceId (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseDeviceId. Error is not specified!" << endl;
	}
}
void ReleaseCLObjectsManager::releaseContext(cl_context context) {
	cl_int error = clReleaseContext(context);
	
	if (error == CL_INVALID_CONTEXT) {
		cerr << "Error in releaseContext (CL_INVALID_CONTEXT)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseContext. Error is not specified!" << endl;
	}
}
void ReleaseCLObjectsManager::releaseCommandQueue(cl_command_queue commandQueue) {
	cl_int error = clReleaseCommandQueue(commandQueue);
	
	if (error == CL_INVALID_CONTEXT) {
		cerr << "Error in releaseCommandQueue (CL_INVALID_CONTEXT)." << endl;
	}
	else if (error == CL_INVALID_DEVICE) {
		cerr << "Error in releaseCommandQueue (CL_INVALID_DEVICE)." << endl;
	}
	else if (error == CL_INVALID_VALUE) {
		cerr << "Error in releaseCommandQueue (CL_INVALID_VALUE)." << endl;
	}
	else if (error == CL_INVALID_QUEUE_PROPERTIES) {
		cerr << "Error in releaseCommandQueue (CL_INVALID_QUEUE_PROPERTIES)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in releaseCommandQueue (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseCommandQueue. Error is not specified!" << endl;
	}
}

void ReleaseCLObjectsManager::releaseMemObject(cl_mem mem) {
	cl_int error = clReleaseMemObject(mem);

	if (error == CL_INVALID_MEM_OBJECT) {
        //cerr << "Error in releaseMemObject (CL_INVALID_MEM_OBJECT)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseMemObject. Error is not specified!" << endl;
	}
}
void ReleaseCLObjectsManager::releaseKernel(cl_kernel kernel) {
	cl_int error = clReleaseKernel(kernel);

	if (error == CL_INVALID_KERNEL) {
		cerr << "Error in releaseKernel (CL_INVALID_KERNEL)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseKernel. Error is not specified!" << endl;
	}
}
void ReleaseCLObjectsManager::releaseProgram(cl_program program) {
	cl_int error = clReleaseProgram(program);

	if (error == CL_INVALID_PROGRAM) {
		cerr << "Error in releaseProgram (CL_INVALID_PROGRAM)." << endl;
	}
	else if(error == CL_OUT_OF_RESOURCES) {
		cerr << "Error in releaseProgram (CL_OUT_OF_RESOURCES)." << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cerr << "Error in releaseProgram (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if (error != CL_SUCCESS) {
		cerr << "Error in releaseProgram. Error is not specified!" << endl;
	}
}
