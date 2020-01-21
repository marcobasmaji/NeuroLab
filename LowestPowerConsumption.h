#pragma once
#include "Mode.h"
#ifndef LOWESTPOWERCONSUMPTION_H_
#define LOWESTPOWERCONSUMPTION_H_
#endif // !LOWESTPOWERCONSUMPTION.H
#include <vector>
#include "Hardware.h"

class LowestPowerConsumption :
	public Mode
{
	public:
	LowestPowerConsumption();
 std::vector<Hardware> Mode::distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

