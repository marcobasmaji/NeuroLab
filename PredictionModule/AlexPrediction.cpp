#include "AlexPrediction.h"
#pragma once
#include "Prediction.h"
#include "DataResults.h"
#include<string>
#include<utility>
#include<list>
#include<iostream>


int Prediction::getTotalSeconds() {
	return TotalSeconds;
}

void Prediction::setTotalSeconds(int TotalDuration)
{
	TotalSeconds = TotalDuration;
}

int Prediction::getTotalPowerConsumption()
{
	return TotalPowerConsumption;
}

void Prediction::setTotalPowerConsumption(int TotalPowerConsumption)
{
	this->TotalPowerConsumption = TotalPowerConsumption;
}

void Prediction::execute(int numberOfImages, std::vector<std::string> listOfAvailableHardware, std::string operationmode)
{
	std::string highestPerformance = "HighestPerformance";
	std::string lowestPowerConsumption = "LowestPowerConsumption";
	std::string highestEfficiency = "HighestEfficiency";

	if (operationmode.compare(highestPerformance)) {
	}

	if (operationmode.compare(highestEfficiency)) {
	}

	if (operationmode.compare(lowestPowerConsumption)) {
	}
	/*createHardwareDistribution();
	calculateTimes();
	setTotalSeconds();
	calculatePowerConsumption();
	calculateTotalPowerConsumption();
	return;
	*/
}

Prediction::Prediction()
{
	TotalSeconds = 0;
	TotalPowerConsumption = 0;
	PowerConsumption = {};
	Times = {};
	HardwareDistribtution = {};
	
}

void Prediction::setPowerConsumption(double powerConsumption) {
	this->PowerConsumption = PowerConsumption;
}


void Prediction::setTimes(std::vector<double>& times) {
	this->Times = Times;
}


void Prediction::setHardwareDistribution()
{
}

std::list<std::pair<int, std::string>> Prediction::getPowerConsumption()
{
	return PowerConsumption;
}

std::list<std::pair<int, std::string>> Prediction::getTimes()
{
	return Times;
}

std::list<std::pair<int, std::string>> Prediction::getHardwareDistribtution()
{
	return HardwareDistribtution;
}





