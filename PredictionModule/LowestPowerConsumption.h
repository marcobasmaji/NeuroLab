#pragma once
#include "Mode.h"
#include <vector>
#include "Hardware.h"
class LowestPowerConsumption :
	public Mode
{
	std::vector<Hardware> distributeAndPredict(std::vector<std::string>& hardware, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

