#pragma once
#include "Mode.h"
	
class HighestEfficiency :
	public Mode
{
public:

	std::vector<Hardware> Mode::distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	static bool sortbytime(Hardware& a, Hardware& b);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

