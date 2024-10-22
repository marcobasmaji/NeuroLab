#include "PredictionController.h"
#include "Mode.h"
#include "AlexPrediction.h"
#include "NeuroPrediction.h"
#include <iostream>
/**
 * @brief basically creates the desired prediction class.
 * 
 * @param availableHardware 
 * @param Operationmode 
 * @param numberOfImages 
 * @param NN 
 * @return DataResults 
 */
DataResults PredictionController::calculatePrediction(int numberOfImages,std::string NN, std::string Operationmode,std::vector<std::string>& availableHardware)
{
	std::string alexnet = "ALEXNET";
	std::string neuronet = "NEUROLABNET";
	if (NN.compare(alexnet) == 0) {
		AlexPrediction *alex = new AlexPrediction;
		Mode* mode = alex->chooseMode(Operationmode);
		std::vector<Hardware> vectorResults = (mode->distributeAndPredict(availableHardware, numberOfImages));
		DataResults*  results = new DataResults(vectorResults);
		delete mode;
		delete alex;
		return *results;
	}
	if (NN.compare(neuronet) == 0) {
		NeuroPrediction* neuro = new NeuroPrediction();
		std::vector<Hardware> vectorResults = neuro->distributeAndPredict(availableHardware, numberOfImages);
		DataResults* results = new DataResults(vectorResults);
		delete neuro;
		return *results;

	}
	else // alternative for this 
	{
		NeuroPrediction* neuro = new NeuroPrediction();
		std::vector<Hardware> vectorResults = neuro->distributeAndPredict(availableHardware, numberOfImages);
		DataResults* results = new DataResults(vectorResults);
		delete neuro;
		return *results;

	}
}

