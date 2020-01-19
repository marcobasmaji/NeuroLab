#include "PredictionController.h"
#include "Mode.h"
#include <iostream>

DataResults PredictionController::calculatePredictionType(std::vector<std::string>& availableHardware, std::string Operationmode, int numberOfImages, std::string NN)
{
	std::string alexnet = "Alexnet";
	std::string neuronet = "neuronet";
	if (NN.compare(alexnet) == 0) {
		AlexPrediction alex = PredictionController::createPrediction(availableHardware, Operationmode, numberOfImages);
		Mode mode = alex.chooseMode(Operationmode);
		mode.
	}
	if (NN.compare(neuronet) == 0) {
		NeuroPrediction neuro = PredictionController::makePrediction(availableHardware, Operationmode, numberOfImages);
	}
}

AlexPrediction PredictionController::createPrediction(std::vector<std::string>& hardware,std::string operationnmode , int numberOfImages)
{
	std::string lowestPowerconsumption = "LowestPowerConsumption";
	std::string Highestefficiency = "HighestEfficiency";
	std::string HighestPerformance = "HighestPerformance";
	if (operationmode.compare(lowestPowerconsumption) == 0) {}
	if (operationmode.compare(Highestefficiency) == 0) {}
	if (operationmode.compare(HighestPerformance) == 0) {}
	else {
		std::cerr << "The operationmode is not known to the program please select another one";
	}


	
}

NeuroPrediction PredictionController::makePrediction(std::vector<std::string>& hardware, std::string operationmode, int numberOfImages)
{
	return NeuroPrediction();
}
