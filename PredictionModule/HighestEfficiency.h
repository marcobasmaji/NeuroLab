#pragma once
#include "Mode.h"
class HighestEfficiency :
	public Mode
{
	
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

