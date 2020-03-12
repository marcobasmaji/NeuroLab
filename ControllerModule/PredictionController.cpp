#include "PredictionController.h"
#include "PredictionModule/Mode.h"
#include "PredictionModule/AlexPrediction.h"
#include "PredictionModule/NeuroPrediction.h"
#include <iostream>
/**
 * @brief basically creates the desired prediction class and acts as a 
 * 
 * @param availableHardware a vector of strings containing the names of the hardware elements
 * @param Operationmode a string containing the operation mode
 * @param numberOfImages an integer that contains the number of images that need to be classified
 * @param NN a string containing the name of the nn we are using
 * @return DataResults a resulsts that contains the important facts about the prediciton
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
        //delete mode;
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

