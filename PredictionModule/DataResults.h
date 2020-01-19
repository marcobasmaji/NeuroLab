#pragma once
#include<vector>
#include <string>
class DataResults
{
public:
	std::vector<std::pair<std::string, int>> hardwareDistribution;
	std::vector<std::pair<std::string, double>> Times;
	std::vector<std::pair<std::string, double>> PowerConsumption;
	double TotalPowerConsumption;
	double TotalTime;
	DataResults(std::vector<std::pair<std::string, int>>& hardwareDistribution,
	std::vector<std::pair<std::string, double>>& Times,
	std::vector<std::pair<std::string, double>>& PowerConsumption);

};

