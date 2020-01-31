#pragma once
#include <list>
#include <vector>
#include "../PredictionModule/AlexPrediction.h"
#include "../PredictionModule/NeuroPrediction.h"
#include "../PredictionModule/DataResults.h"
class PredictionController
{
public:
	DataResults calculatePrediction(int numberOfImages, std::string NN, std::string Operationmode, std::vector<std::string>& availableHardware);
	

	
};



