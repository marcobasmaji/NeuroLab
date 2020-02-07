#pragma once
#include "Mode.h"
/**
 * @brief .h file for the highest efficiency mode
 * eclaration of the distributeAndPredict function as well as the TimeValueOfX function
 */
class HighestEfficiency :
	public Mode
{
public:

	std::vector<Hardware>distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

