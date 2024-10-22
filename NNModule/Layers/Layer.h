#ifndef LAYER_H
#define LAYER_H

#include <HardwareModule/OpenCL/OpenCLLayer.hpp>

class Layer {
public:
    virtual void forwardPass() = 0;
    virtual void backPropagate() = 0;
    virtual OpenCLLayer* getCLLayer()=0;
};

#endif // LAYER_H
