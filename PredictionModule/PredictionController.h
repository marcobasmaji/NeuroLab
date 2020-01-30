#pragma once
#include <list>
#include <vector>
#include "AlexPrediction.h"
#include "NeuroPrediction.h"
#include "DataResults.h"
class PredictionController
{
public:
	DataResults calculatePredictionType(std::vector<std::string>& availableHardware,std::string Operationmode, int numberOfImages,std::string NN);
	

	
};



