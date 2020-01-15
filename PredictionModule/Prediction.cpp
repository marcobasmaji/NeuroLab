
#pragma once
#include "Prediction.h"
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

	void Prediction::setPowerConsumption(std::list<std::pair<int, std::string>>& PowerConsumption)
	{
		this->PowerConsumption = PowerConsumption;
	}

	void Prediction::setTimes(std::list<std::pair<int, std::string>>& Times)
	{
		this->Times = Times;
	}

	void Prediction::setHardwareDistribution(std::list<std::pair<int, std::string>>& HardwareDistribution)
	{
		this->HardwareDistribtution = HardwareDistribution;
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


Prediction::Prediction(int numberOfImages, std::list<std::string> listOfAvailableHardware, std::string operationmode)
{
	TotalSeconds = 0;
	TotalPowerConsumption = 0;
	PowerConsumption = {};
	Times = {};
	HardwareDistribtution = {};
}

enum HardwareElement{Movidius1,Movidius2, Movidius3,Movidius4, CPU, FPGA};
