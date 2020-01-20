#pragma once
#include <utility>
#include <list>
#include <string>
#include "Hardware.h"

class Mode
{
public:
	virtual std::vector<Hardware>distributeAndPredict(std::vector<std::string>& hardware, int numberOfImages) = 0;
	//virtual double timeValueOfX(std::vector<double>& polynome, double x);
};

