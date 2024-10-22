#pragma once
#include "Mode.h"
#ifndef LOWESTPOWERCONSUMPTION_H_
#pragma once
#define LOWESTPOWERCONSUMPTION_H_
#endif // !LOWESTPOWERCONSUMPTION.H
#include <vector>
#include "Hardware.h"
/**
 * @brief .h file for the lowest power consumption class
 * contains the declaration of a constructor and two methods
 */
class LowestPowerConsumption :
	public Mode
{
	public:
	LowestPowerConsumption();
 std::vector<Hardware> distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

