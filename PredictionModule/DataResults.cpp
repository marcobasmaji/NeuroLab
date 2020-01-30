#include "DataResults.h"
#include "Hardware.h"


DataResults::DataResults(std::vector<Hardware>& results) {
	std::vector<std::pair<std::string, int>> hDistribution;
	std::vector<std::pair<std::string, double>> times;
	std::vector<std::pair<std::string, double>> pConsumption;
	std::vector<std::pair<std::string, double>> flops;
	std::vector<std::pair<std::string, double>> bandwith;
	double TotalPowerConsumption = 0;
	double TotalRequiredTime = 0;
	
	
	for (auto i = results.begin(); i != results.end(); i++) {
		std::pair<std::string, int> hardwareV = std::make_pair(i->name,i->numberOfAssignedImages);
		hDistribution.push_back(hardwareV);
		std::pair<std::string, double> time = std::make_pair(i->name, i->requiredTime);
		times.push_back(time);
		double powerConsumptionHardware = (i->requiredTime*i->powerconsumption);
		std::pair<std::string, double> cons = std::make_pair(i->name, powerConsumptionHardware);
		pConsumption.push_back(cons);
		TotalPowerConsumption = TotalPowerConsumption + powerConsumptionHardware;

	}
	this->hardwareDistribution = hDistribution;
	this->PowerConsumption = pConsumption;
	this->Times = times;
	this->TotalTime = times.back().second;
	this->TotalPowerConsumption = TotalPowerConsumption;
}
