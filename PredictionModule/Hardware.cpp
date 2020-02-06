#include "Hardware.h"
#include <string>
/**
 * @brief Construct a new Hardware:: Hardware object
 * 
 * @param name  a string containing the name of the hardware element
 * @param numberOfassignedImages an integer containing the desired number of images to be classified
 * @param requiredTime a double containing the times in seconds it takes the hardware to classify the images
 * @param polynome a polynome(stored as a double vector) that is specific for the hardware and used to determine the requiredTime
 * @param powerconsumption a double containing the powerconsumption of the hardware element per second
 * @param flops an integer containing the amount of flops this operation needs
 * @param bandwith an integer containing the bandiwth of the hardware device
 */
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



