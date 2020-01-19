#pragma once
#include "Mode.h"
#include <vector>
#include "Hardware.h"

class HighestPerformance :
	public Mode	
{
public:
	std::vector<Hardware>distributeAndPredict(std::vector<std::string>& hardwares, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

