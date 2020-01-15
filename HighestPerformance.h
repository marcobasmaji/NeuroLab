#pragma once
#include "Mode.h"
class HighestPerformance :
	public Mode	
{
public:
	std::vector<std::pair<std::string, int>>distribute(std::list<std::string>& hardwares, int numberOfImages);
	double ValueAtX(double polynome [] , double x) {}
};

