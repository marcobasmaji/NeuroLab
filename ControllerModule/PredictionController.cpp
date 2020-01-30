#include "PredictionController.h"
#include "PredictionModule/Mode.h"
#include "PredictionModule/AlexPrediction.h"
#include "PredictionModule/NeuroPrediction.h"
#include <iostream>
/**
 * @brief basically creates the desired prediction class and acts as a 
 * 
 * @param availableHardware 
 * @param Operationmode 
 * @param numberOfImages 
 * @param NN 
 * @return DataResults 
 */
DataResults PredictionController::calculatePrediction(int numberOfImages,std::string NN, std::string Operationmode,std::vector<std::string>& availableHardware)
{
	std::string alexnet = "Alexnet";
	std::string neuronet = "neuronet";
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

