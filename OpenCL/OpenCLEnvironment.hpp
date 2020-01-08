//checked

#pragma once

#include "CL/cl.h"
#include "HardwareEnvironment.hpp"
#include "ReleaseCLObjectsManager.hpp"

class OpenCLEnvironment : HardwareEnvironment {

public:
	OpenCLEnvironment();
	~OpenCLEnvironment();

	//setters
	void setPlatformId(cl_platform_id platformId);
	void setDeviceId(cl_device_id deviceId);
	void setContext(cl_context context);
	void setCommandQueue(cl_command_queue commandQueue);

	//getters
	cl_platform_id getPlatformId();
	cl_device_id getDeviceId();
	cl_context getContext();
	cl_command_queue getCommandQueue();

private:
	cl_platform_id platformId=nullptr;
	cl_device_id deviceId = nullptr;
	cl_context context = nullptr;
	cl_command_queue commandQueue = nullptr;

	ReleaseCLObjectsManager* releaseCLObjectsManager=nullptr;

	void releaseResources();
};
