#include "DataResults.h"
#include "Hardware.h"

/**
 * @brief Construct a new Data Results:: Data Results object
 * contains all the important data that is used for the classifcation
 * @param results a vector that represents a optimal constellation of hardware elements
 */
DataResults::DataResults(std::vector<Hardware>& results) {
	std::vector<std::pair<std::string, int>> hDistribution;
	std::vector<std::pair<std::string, double>> times;
	std::vector<std::pair<std::string, double>> pConsumption;
	std::vector<std::pair<std::string, double>> flops;
	std::vector<std::pair<std::string, double>> bandwidth;
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
		double totalFlops = 0;
		double totalNumberOfImages = 0;
		//double flopsHardware = totalFlops * (totalNumberOfImages / i->numberOfAssignedImages);
		double flopshardware = (i->flops * i->requiredTime);
		std::pair<std::string, double> flopspair = std::make_pair(i->name, flopshardware);
		flops.push_back(flopspair);
		double bandwidthhardware = i->bandwidth * i->numberOfAssignedImages;
		std::pair < std::string, double> bandwidthpair = std::make_pair(i->name, bandwidthhardware);
		bandwidth.push_back(bandwidthpair);
		// gibt probleme wenn die numberofassignedimages 0 ist
		TotalPowerConsumption = TotalPowerConsumption + powerConsumptionHardware;

	}
	this->hardwareDistribution = hDistribution;
	this->PowerConsumption = pConsumption;
	this->Times = times;
	this->TotalTime = times.back().second;
	this->TotalPowerConsumption = TotalPowerConsumption;
	this->Bandwidth = bandwidth;
	this->Flops = flops;
}
