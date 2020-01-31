#include "HardwareSurveillence.h"

HardwareSurveillence::HardwareSurveillence(){

}
//checks only CPU, FPGA and Movidius stick availability
vector<string> HardwareSurveillence::checkWithOpenVino(){
    return core.GetAvailableDevices();
}

//checks GPU availability
bool HardwareSurveillence::checkWithOpenCL(){


    cl_uint num_platforms;
    clGetPlatformIDs(0, NULL, &num_platforms);
    cl_platform_id *platforms = (cl_platform_id*)malloc(num_platforms*sizeof(cl_platform_id));
    clGetPlatformIDs(num_platforms, platforms, NULL);
    cl_platform_id platform=platforms[0];

    cl_uint num_devices;
    clGetDeviceIDs(platform, CL_DEVICE_TYPE_GPU, 0, NULL, &num_devices);

    delete platforms;

    return num_devices!=0;
}

vector<string> HardwareSurveillence::checkAvailableHardware(){
    vector<string> devices = checkWithOpenVino();
    //vector<string> devicesOpenCL = checkWithOpenCL();

    /*for(string device : devicesOpenCL){
        devices.push_back(device);

    }*/

    //return devices;
    return devices;

}
