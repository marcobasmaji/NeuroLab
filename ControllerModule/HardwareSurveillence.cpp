#include "HardwareSurveillence.h"

HardwareSurveillence::HardwareSurveillence(){

}
//checks only CPU, FPGA and Movidius stick availability
vector<string> HardwareSurveillence::checkWithOpenVino(){
    return core.GetAvailableDevices();
}

//checks GPU availability
vector<string> HardwareSurveillence::checkWithOpenCL(){

    vector<string> devices;
    cl_platform_id *platform = NULL;
    clGetPlatformIDs(sizeof (cl_uint), platform, NULL);
    if(clGetDeviceIDs(*platform, CL_DEVICE_TYPE_GPU, sizeof(cl_uint), NULL, NULL) == CL_SUCCESS){
        devices.push_back("GPU");
    }
    return devices;
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
