#pragma once
#include "Mode.h"
class HighestEfficiency :
	public Mode
{
	std::vector<Hardware> Mode::distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

