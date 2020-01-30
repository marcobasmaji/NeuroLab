#pragma once
#include <list>
#include <vector>
#include "AlexPrediction.h"
#include "NeuroPrediction.h"
#include "DataResults.h"
class PredictionController
{
public:
	DataResults calculatePrediction(int numberOfImages, std::string NN, std::string Operationmode, std::vector<std::string>& availableHardware);
	

	
};



