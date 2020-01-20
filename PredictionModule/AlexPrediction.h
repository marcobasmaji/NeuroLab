#pragma once
#include "Prediction.h"
#include"Mode.h"
class AlexPrediction :
	public Prediction
{
	Mode* chooseMode(std::string operationmode);
};

