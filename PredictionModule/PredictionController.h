#pragma once
#include <list>
#include <string>
#include "AlexPrediction.h"
#include "NeuroPrediction.h"
class PredictionController
{
public:
	void calculatePredictionType(std::list<std::string> availableHardware,std::string Operationmode, int numberOfImages,std::string NN);
	AlexPrediction createPrediction(std::vector<std::string>& hardware,std::string operationmode , int numberOfImages);
	NeuroPrediction makePrediction(std::vector<std::string>& hardware,std::string operationmode, int numberOfImages);

	
};



