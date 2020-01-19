#include "Hardware.h"
#include <string>

Hardware::Hardware(std::string name, int numberOfassignedImages, double requiredTime, std::vector<double>& polynome, double powerconsumption)
{
	this->name = name;
	this->numberOfAssignedImages = numberOfAssignedImages;
	this->requiredTime = requiredTime;
	this->polynome = polynome;
	this->powerconsumption = powerconsumption;
}

bool Hardware::sortbytime(Hardware& a, Hardware& b)
{
	return (a.requiredTime < b.requiredTime);
}
