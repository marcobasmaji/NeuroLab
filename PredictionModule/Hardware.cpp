#include "Hardware.h"
#include <string>

Hardware::Hardware(std::string name, int numberOfassignedImages, double requiredTime, std::vector<double>& polynome, double powerconsumption, double flops, double bandwith)
{
	this->name = name;
	this->numberOfAssignedImages = numberOfAssignedImages;
	this->requiredTime = requiredTime;
	this->polynome = polynome;
	this->powerconsumption = powerconsumption;
	this->bandwidth = bandwidth;
	this->flops = flops;
}



