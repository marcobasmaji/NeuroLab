#pragma once
#include "Prediction.h"
#include"Mode.h"
class AlexPrediction :
	public Prediction
{
public:
	Mode* chooseMode(std::string operationmode);
};

