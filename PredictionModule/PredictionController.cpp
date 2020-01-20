#include "PredictionController.h"
#include "Mode.h"
#include "AlexPrediction.h"
#include <iostream>

DataResults PredictionController::calculatePredictionType(std::vector<std::string>& availableHardware, std::string Operationmode, int numberOfImages, std::string NN)
{
	std::string alexnet = "Alexnet";
	std::string neuronet = "neuronet";
	if (NN.compare(alexnet) == 0) {
		AlexPrediction alex = new AlexPrediction();
		Mode *mode = alex.chooseMode(Operationmode);
		DataResults results = DataResults((mode->distributeAndPredict(availableHardware, numberOfImages)));
		delete mode;
		return results;
	}
	if (NN.compare(neuronet) == 0) {
		NeuroPrediction neuro = PredictionController::makePrediction(availableHardware, Operationmode, numberOfImages);
	}
}

AlexPrediction PredictionController::createPrediction(std::vector<std::string>& hardware,std::string operationnmode , int numberOfImages)
{
	


	
}

NeuroPrediction PredictionController::makePrediction(std::vector<std::string>& hardware, std::string operationmode, int numberOfImages)
{
	return NeuroPrediction();
}
