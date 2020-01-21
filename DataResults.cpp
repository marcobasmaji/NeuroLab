#include "DataResults.h"
#include "Hardware.h"


DataResults::DataResults(std::vector<Hardware>& results) {
	std::vector<std::pair<std::string, int>> hDistribution;
	std::vector<std::pair<std::string, double>> times;
	std::vector<std::pair<std::string, double>> pConsumption;
	double TotalPowerConsumption = 0;
	
	for (auto element : results) {
		std::pair<std::string, int> hardwareV = std::make_pair(element.name, element.numberOfAssignedImages);
		hDistribution.push_back(hardwareV);
		std::pair<std::string, double> time = std::make_pair(element.name, element.requiredTime);
		times.push_back(time);
		std::pair<std::string, double> cons = std::make_pair(element.name, element.powerconsumption);
		pConsumption.push_back(cons);
		TotalPowerConsumption = TotalPowerConsumption + element.powerconsumption;
	}
	this->hardwareDistribution = hDistribution;
	this->PowerConsumption = pConsumption;
	this->Times = times;
	this->TotalTime = times.back().second;
	this->TotalPowerConsumption = TotalPowerConsumption;
}
