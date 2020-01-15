#pragma once
#include <list>
#include <string>
class PredictionController
{
public:
	void calculatePrediction(std::list<std::string> availableHardware,std::string Operationmode, int numberOfImages,std::string NN);
};



