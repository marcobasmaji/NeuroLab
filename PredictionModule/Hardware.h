#pragma once
#include <vector>
#include <string>
/**
 * @brief declaration of the attributes of the hardware class and its constructor
 * 
 */
class Hardware
{
public:
	std::string name;
	int numberOfAssignedImages;
	double requiredTime;
	std::vector<double> polynome;
	double powerconsumption;
	double flops;
	double bandwidth;
	Hardware(std::string name,int numberOfassignedImages, double requiredTime, std::vector<double>& polynome, double powerconsumption, double flops, double bandwidth);


	
	
};

