#pragma once
#include<vector>
#include <string>
#include "Hardware.h"
/**
 * @brief declaration of the dataResults class contains 4 vectors and two doubles as attributes and a constructor
 * 
 */
class DataResults
{
public:
	std::vector<std::pair<std::string, int>> hardwareDistribution;
	std::vector<std::pair<std::string, double>> Times;
	std::vector<std::pair<std::string, double>> PowerConsumption;
	std::vector<std::pair<std::string, double>> Flops;
	std::vector<std::pair<std::string, double>> Bandwidth;
	double TotalPowerConsumption;
	double TotalTime;
	DataResults(std::vector<Hardware>& results);

};

