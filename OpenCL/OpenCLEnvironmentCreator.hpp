//checked

#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include "CL/cl.h"
#include "OpenCLLayer.hpp"
#include "Layer.hpp"
#include "OpenCLEnvironment.hpp"
#include "HardwareType.hpp"

class OpenCLEnvironmentCreator {
public:
    OpenCLEnvironment* createOpenCLEnvironment(enum HardwareType hardwareType);

private:
    cl_platform_id* getPlatforms(cl_uint* numEntries);
    cl_device_id* getDevices(cl_platform_id platformId, cl_device_type deviceType, cl_uint* numDevices);
    cl_context getContext(cl_device_id deviceId);
    cl_command_queue createCommandQueue(cl_context context, cl_device_id deviceId);
};
