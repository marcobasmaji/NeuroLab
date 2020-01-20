#include "AlexPrediction.h"
#pragma once
#include "Prediction.h"
#include "DataResults.h"
#include "LowestPowerConsumption.h"
#include "HighestEfficiency.h"
#include "HighestPerformance.h"
#include<string>
#include<iostream>
/**
 * @brief 
 * 
 * @param operationmode 
 * @return Mode* a pointer of the 
 */
Mode* AlexPrediction::chooseMode(std::string operationmode)
{
	std::string lowestPowerconsumption = "LowestPowerConsumption";
	std::string highestefficiency = "HighestEfficiency";
	std::string highestPerformance = "HighestPerformance";
	if (operationmode.compare(lowestPowerconsumption) == 0) {
		LowestPowerConsumption* l = new LowestPowerConsumption();
		return l;
	}
	if (operationmode.compare(highestefficiency) == 0) {
		HighestEfficiency* h = new HighestEfficiency();
		return h;
	}
	else (operationmode.compare(highestPerformance) == 0); {
		HighestPerformance* hp = new HighestPerformance();
		return hp;
	}
	
}
