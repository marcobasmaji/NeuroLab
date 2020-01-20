#include "AlexPrediction.h"
#pragma once
#include "Prediction.h"
#include "DataResults.h"
#include "LowestPowerConsumption.h"
#include<string>
#include<iostream>

Mode AlexPrediction::chooseMode(std::string operationmode)
{
	std::string lowestPowerconsumption = "LowestPowerConsumption";
	std::string Highestefficiency = "HighestEfficiency";
	std::string HighestPerformance = "HighestPerformance";
	if (operationmode.compare(lowestPowerconsumption) == 0) {
		LowestPowerConsumption l = new LowestPowerConsumption();
	return }
	if (operationmode.compare(Highestefficiency) == 0) {}
	if (operationmode.compare(HighestPerformance) == 0) {}
	else {
		std::cerr << "The operationmode is not known to the program please select another one";
	}
}
