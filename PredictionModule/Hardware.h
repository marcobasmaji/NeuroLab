#pragma once
#include <vector>
class Hardware
{
public:
	std::string name;
	int numberOfAssignedImages;
	double requiredTime;
	std::vector<double> polynome;
	double powerconsumption;
	Hardware(std::string name,int numberOfassignedImages, double requiredTime, std::vector<double>& polynome, double powerconsumption);
	bool sortbytime(Hardware& a, Hardware& b);

	
	
};

