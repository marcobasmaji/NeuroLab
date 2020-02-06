#pragma once
#include "Mode.h"
#include <vector>
#include "Hardware.h"
/**
 * @brief .h file of the highest performance class
 * contains the declaration of the constructors and two methdos 
 */
class HighestPerformance :
	public Mode	
{
public:
	HighestPerformance();
	std::vector<Hardware> distributeAndPredict(std::vector<std::string>& name, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x);
};

