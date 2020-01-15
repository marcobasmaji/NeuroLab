#pragma once
#include<vector>
#include<string>
#include <utility>

class Prediction
{
private:
	int TotalSeconds;
	int TotalPowerConsumption;
	std::vector<std::pair<int, std::string>> PowerConsumption;
	std::vector<std::pair<int, std::string>> Times;
	std::vector<std::pair<int, std::string>> HardwareDistribtution;
public:
	Prediction(int numberOfImages, std::vector<std::string> vectorOfAvailableHardware, std::string operationmode);

	virtual void setTotalSeconds(int TotalDuration);
	virtual void execute(int numberOfImages, std::vector<std::string> vectorOfAvailableHardware, std::string operationmode) = 0;
	virtual void setTotalPowerConsumption(int TotalPowerConsumption);
	virtual void setPowerConsumption();
	virtual void setTimes();
	virtual void setHardwareDistribution();
	virtual int getTotalPowerConsumption();
	virtual int getTotalSeconds();
	virtual std::vector<std::pair<int, std::string>> getPowerConsumption();
	virtual std::vector<std::pair<int, std::string>> getTimes();
	virtual std::vector<std::pair<int, std::string>> getHardwareDistribtution();
};


