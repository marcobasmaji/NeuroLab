/**
*   @brief  This class is just for creating an OpenCLEnvironment object and initilizes its attributes. It creates an OpenCLEnvironment for the overhanded hardware device type and just have to be created once.
*/

#pragma once

#define CL_USE_DEPRECATED_OPENCL_1_2_APIS

#include "CL/cl.h"
#include "OpenCLLayer.hpp"
#include "OpenCLEnvironment.hpp"
#include "HardwareType.hpp"

class OpenCLEnvironmentCreator {
public:
    /**
    *   @brief  			This function is the interface to this class. It creates an OpenCLEnvironment object and initializes all its values depending on the overhanded hardwareType. It accepts values like GPU, CPU and FPGA. So it just has to be called once at the very beginning for every hardware type to get an OpenCLEnvironment class for this device. Although there might be many different platforms and devices it just selects one.
    *   @param hardwareType This attribute selects the hardware for which the OpenCLEnvironment class will be created.
    *   @return 			The return value is the initialized OpenCLEnvironment object that has been created of the desired hardware type.
    */
    OpenCLEnvironment* createOpenCLEnvironment(enum HardwareType hardwareType);

private:
    /**
    *   @brief  			This function just calls the OpenCL function clGetPlatformsIDs and the found ones. It also logs possible errors.
    *   @param numEntries 	This attribute has to be allocated using malloc and holds the number of platforms found after calling this function.
    *   @return				The return value is an array of platform ids.
    */
    cl_platform_id* getPlatforms(cl_uint* numEntries);

    /**
    *   @brief  			This function just calls the OpenCL function clGetDevicesIDs, returns all the device ids for the overhanded device type, handles possible errors and logs them.
    *   @param  platformId  This attribute is the platform id for which the device ids will be returned.
    *   @param  deviceType  This attribute restricts the device type for which the device ids will be returned.
    *   @param  numDevices  This attribute has to be allocated using malloc and holds the number of devices found after calling this function.
    *   @return 			The return value is an array of device ids.
    */
    cl_device_id* getDevices(cl_platform_id platformId, cl_device_type deviceType, cl_uint* numDevices);
    /**
    *   @brief   			This function just calls the OpenCL function clCreateContext, logs all possible errors alongside and returns the created context.
    *   @param  deviceId    The device id for which the context should be created. For simplicity, our project just uses one device per context. Therefor just one device id can be overhanded.   
    *   @return 			The created context.
    */
    cl_context getContext(cl_device_id deviceId);
    /**
    *   @brief  		This function just calls the OpenCL function clCreateCommandQueue, logs all possible errors alongside and returns the created command queue.
    *   @param context  The context for which the command queue will be created.
    *   @param deviceId The device id for which the command queue will be created.
    *   @return 		The created command queue.
    */
    cl_command_queue createCommandQueue(cl_context context, cl_device_id deviceId);
};
