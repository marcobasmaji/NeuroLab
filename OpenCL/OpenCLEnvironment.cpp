//checked

#include "OpenCLEnvironment.hpp"

#include <iostream>

using namespace std;

OpenCLEnvironment::OpenCLEnvironment() {
	releaseCLObjectsManager = new ReleaseCLObjectsManager();
}
OpenCLEnvironment::~OpenCLEnvironment() {
	releaseResources();

	delete releaseCLObjectsManager;
}

void OpenCLEnvironment::setPlatformId(cl_platform_id platformId) { this->platformId = platformId; }
void OpenCLEnvironment::setDeviceId(cl_device_id deviceId) {
	if (this->deviceId) {
		releaseCLObjectsManager->releaseDeviceId(this->deviceId);
	}

	this->deviceId = deviceId;
}
void OpenCLEnvironment::setContext(cl_context context) {
	if (this->context) {
		releaseCLObjectsManager->releaseContext(this->context);
	}

	this->context = context;
}
void OpenCLEnvironment::setCommandQueue(cl_command_queue commandQueue) {
	if (this->commandQueue) {
		releaseCLObjectsManager->releaseCommandQueue(this->commandQueue);
	}

	this->commandQueue = commandQueue;
}

//getters
cl_platform_id OpenCLEnvironment::getPlatformId() { return platformId; }
cl_device_id OpenCLEnvironment::getDeviceId() {	return deviceId; }
cl_context OpenCLEnvironment::getContext() { return context; }
cl_command_queue OpenCLEnvironment::getCommandQueue() { return commandQueue; }

void OpenCLEnvironment::releaseResources() {
	cl_int error = clFlush(commandQueue);

	if (error == CL_INVALID_COMMAND_QUEUE) {
		cout << "Fehler in releaseRessources (CL_INVALID_COMMAND_QUEUE)" << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cout << "Error in releaseMemObject (CL_OUT_OF_HOST_MEMORY)." << endl;
	}
	else if(error!=CL_SUCCESS) {
		cout << "Error in releaseMemObject. Error is not specified!" << endl;
	}

	error = clFinish(commandQueue);

	if (error == CL_INVALID_COMMAND_QUEUE) {
		cout << "Fehler in releaseRessources (CL_INVALID_COMMAND_QUEUE )" << endl;
	}
	else if (error == CL_OUT_OF_HOST_MEMORY) {
		cout << "Error in releaseMemObject (CL_OUT_OF_HOST_MEMORY )." << endl;
	}
	else if (error != CL_SUCCESS) {
		cout << "Error in releaseMemObject. Error is not specified!" << endl;
	}

	releaseCLObjectsManager->releaseCommandQueue(commandQueue);
	releaseCLObjectsManager->releaseContext(context);
	releaseCLObjectsManager->releaseDeviceId(deviceId);
}
