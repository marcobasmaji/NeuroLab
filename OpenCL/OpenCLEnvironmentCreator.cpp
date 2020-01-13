//checked

#include <iostream>

#include "OpenCLEnvironmentCreator.hpp"

using namespace std;

OpenCLEnvironment* OpenCLEnvironmentCreator::createOpenCLEnvironment(enum HardwareType hardwareType) {
    cl_uint* numEntries = (cl_uint*)malloc(sizeof(cl_uint));
    cl_platform_id platformId = getPlatforms(numEntries)[0];
    cl_uint* numDevices = (cl_uint*)malloc(sizeof(cl_uint));

    cl_device_type deviceType;

    switch (hardwareType) {
    case HardwareType::GPU:
        deviceType = CL_DEVICE_TYPE_GPU;
        break;

    case HardwareType::CPU:
        deviceType = CL_DEVICE_TYPE_CPU;
        break;

    case HardwareType::FPGA:
        deviceType = CL_DEVICE_TYPE_ACCELERATOR;
        break;

    default:
        cerr << "Fehler in createOpenClEnvironment." << endl;
        deviceType = CL_DEVICE_TYPE_DEFAULT;
    }

    cl_device_id deviceId = getDevices(platformId, deviceType, numDevices)[0];
    cl_context context = getContext(deviceId);
    cl_command_queue commandQueue = createCommandQueue(context, deviceId);

    OpenCLEnvironment* environment = new OpenCLEnvironment();
    environment->setPlatformId(platformId);
    environment->setDeviceId(deviceId);
    environment->setContext(context);
    environment->setCommandQueue(commandQueue);

    return environment;
}

cl_platform_id* OpenCLEnvironmentCreator::getPlatforms(cl_uint* numEntries) {

    clGetPlatformIDs(0, NULL, numEntries);
    cl_platform_id* platforms = (cl_platform_id*) malloc(sizeof(cl_platform_id) * (*numEntries));
    cl_int error = clGetPlatformIDs(*numEntries, platforms, NULL);

    if (error == CL_INVALID_VALUE) {
        cerr << "Error in getPlatforms (CL_INVALID_VALUE)." << endl;

        return nullptr;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in getPlatforms. Error is not specified!" << endl;

        return nullptr;
    }

    return platforms;
}

cl_device_id* OpenCLEnvironmentCreator::getDevices(cl_platform_id platform, cl_device_type deviceType, cl_uint* numDevices) {
    clGetDeviceIDs(platform, deviceType, 0, NULL, numDevices);
    cl_device_id* devices = (cl_device_id*)malloc(sizeof(cl_device_id) * (*numDevices));
    cl_int error = clGetDeviceIDs(platform, deviceType, *numDevices, devices, NULL);

    if (error == CL_INVALID_PLATFORM) {
        cerr << "Error in getDevices (CL_INVALID_PLATFORM)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_DEVICE_TYPE) {
        cerr << "Error in getDevices (CL_INVALID_DEVICE_TYPE)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in getDevices (CL_INVALID_VALUE)." << endl;

        return nullptr;
    }
    else if (error == CL_DEVICE_NOT_FOUND) {
        cerr << "Error in getDevices (CL_DEVICE_NOT_FOUND)." << endl;

        return nullptr;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in getDevices. Error is not specified!" << endl;

        return nullptr;
    }

    return devices;
}

cl_context OpenCLEnvironmentCreator::getContext(cl_device_id device) {
    cl_int error;

    cl_context context = clCreateContext(NULL, 1, &device, NULL, NULL, &error);

    if (error == CL_INVALID_PLATFORM) {
        cerr << "Error in getContext (CL_INVALID_PLATFORM)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in getContext (CL_INVALID_VALUE)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_DEVICE) {
        cerr << "Error in getContext (CL_INVALID_DEVICE)." << endl;

        return nullptr;
    }
    else if (error == CL_DEVICE_NOT_AVAILABLE) {
        cerr << "Error in getContext (CL_DEVICE_NOT_AVAILABLE)." << endl;

        return nullptr;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in getContext (CL_OUT_OF_HOST_MEMORY)." << endl;

        return nullptr;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in getContext. Error is not specified!" << endl;

        return nullptr;
    }

    return context;
}

cl_command_queue OpenCLEnvironmentCreator::createCommandQueue(cl_context context, cl_device_id deviceId) {
    cl_int error;

    cl_command_queue commandQueue = clCreateCommandQueue(context, deviceId, 0, &error);

    if (error == CL_INVALID_CONTEXT) {
        cerr << "Error in createCommandQueue (CL_INVALID_CONTEXT)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_DEVICE) {
        cerr << "Error in createCommandQueue (CL_INVALID_DEVICE)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_VALUE) {
        cerr << "Error in createCommandQueue (CL_INVALID_VALUE)." << endl;

        return nullptr;
    }
    else if (error == CL_INVALID_QUEUE_PROPERTIES) {
        cerr << "Error in createCommandQueue (CL_INVALID_QUEUE_PROPERTIES)." << endl;

        return nullptr;
    }
    else if (error == CL_OUT_OF_HOST_MEMORY) {
        cerr << "Error in createCommandQueue (CL_OUT_OF_HOST_MEMORY)." << endl;

        return nullptr;
    }
    else if (error != CL_SUCCESS) {
        cerr << "Error in createCommandQueue. Error is not specified!" << endl;

        return nullptr;
    }

    return commandQueue;
}
