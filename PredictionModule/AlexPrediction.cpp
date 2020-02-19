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
 * @return Mode* a pointer to an object that represents the operation mode
 */
Mode* AlexPrediction::chooseMode(std::string operationmode)
{
    std::string lowestPowerconsumption = "LOWEST_POWER_CONSUMPTION";
    std::string highestefficiency = "HIGHEST_EFFICIENCY";
    std::string highestPerformance = "HIGHEST_PERFORMANCE";
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
