#pragma once
#include "Mode.h"
#include <vector>
#include "Hardware.h"

class HighestPerformance :
	public Mode	
{
public:
	HighestPerformance();
	std::vector<Hardware> Mode::distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

