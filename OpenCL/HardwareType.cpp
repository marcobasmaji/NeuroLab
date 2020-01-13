/**
*   @brief This enum stands for the different Hardware devices our program can access with OpenCL.
*/

#pragma once

enum class HardwareType {
    CPU,   //This value stands for the CPU.
    GPU,   //This value stands for the GPU.
    FPGA   //This value stands for the FPGA.
};
