#pragma once
#include "Prediction.h"
#include"Mode.h"
/**
 * @brief underclass from Prediction declaration of the chooseMode function
 * 
 */
class AlexPrediction :
	public Prediction
{
public:
	Mode* chooseMode(std::string operationmode);
};

