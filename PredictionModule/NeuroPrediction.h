#pragma once
#include "Prediction.h"
#include "Hardware.h"
class NeuroPrediction :
	public Prediction
{
	std::vector<Hardware>distributeAndPredict(std::vector<std::string> availableHardware, int numberOfImages);
	double TimeValueOfX(std::vector<double>& polynome, double x)
	{
	}

};

