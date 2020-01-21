#include "NeuroPrediction.h"
#include <iostream>

NeuroPrediction::NeuroPrediction()
{
}

std::vector<Hardware> NeuroPrediction::distributeAndPredict(std::vector<std::string> availableHardware, int numberOfImages)
{
	std::string cpu = "CPU";
	std::vector<double> polynomCPU{ 1,2,3,4 };
	std::vector<Hardware> list;
	double powerconsumption = 1;
	Hardware example{ cpu,0,(double)9,polynomCPU,powerconsumption };
	for (std::string element : availableHardware) {
		if (element.compare(cpu) == 0) {
			example.name = cpu;
			example.numberOfAssignedImages = numberOfImages;
			example.polynome = polynomCPU;
			example.requiredTime = TimeValueOfX(polynomCPU, numberOfImages);
			example.powerconsumption = example.powerconsumption * example.requiredTime;
			list.push_back(example);
			return list;

		}
	}
	std::cerr << "The CPU is needed with this neural network";
	return list;

}
double NeuroPrediction::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value = 0;
	for (size_t i = 0; i < polynome.size(); i++) {
		int intOfI = i;
		value = value + pow(polynome[polynome.size() - intOfI], x);
	}
	return value;
}

