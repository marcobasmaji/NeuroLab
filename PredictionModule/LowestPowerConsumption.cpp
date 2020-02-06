
#include "LowestPowerConsumption.h"
#include <iostream>
/**
 * @brief Construct a new std::vector<Hardware>Lowest Power Consumption::distribute And Predict object this object is a vector containig one hardware element
 * This hardware element is the detected one with the lowest power consumption
 * @param hardware a reference a vector containing the names of the hardware elements as strings
 * @param numberOfImages an integer that contains the number of images that the user wants to get classified
 */
std::vector<Hardware>LowestPowerConsumption::distributeAndPredict(std::vector<std::string>& hardware, int numberOfImages) {
	std::vector<Hardware> list;
	std::string examplestring = "example";
	double requiredTime = 0;
	std::vector<double>polynomCPU{ -0.0000006,0.0237,1.1126 };
	std::vector<double> polynomFPGA{ 2,3,4,5 };
	std::vector<double>polynomMovidius{ 0.00001, 0.0825, 7.0217 };
	Hardware example{ examplestring,numberOfImages,requiredTime,polynomFPGA,requiredTime,0.0,0.0 };
	std::string CPU = "CPU";
	std::string FPGA = "FPGA";
	std::string sticks[] = { "MYRIAD.1","MYRIAD.2","MYRIAD.3","MYRIAD.4" };
	double powerConsumptionFPGA = 0;
	double powerConsumptionCPU = 100;
	double powerConsumptionMovidius = 10;
	LowestPowerConsumption* low = new LowestPowerConsumption;
	for (std::string movidius : sticks) {
		for (std::string elem : hardware) {
			if (elem.compare(movidius) == 0) {
				example.name = movidius;
				example.polynome = polynomMovidius;
				example.numberOfAssignedImages = numberOfImages;
				example.requiredTime = low->TimeValueOfX(example.polynome,example.numberOfAssignedImages);
				example.powerconsumption = example.requiredTime*powerConsumptionMovidius;
				list.push_back(example);
				return list;
			}

		}
	}
	for (std::string element : hardware) {
		if ((element.compare(CPU)) == 0) {
			example.name = element;
				example.polynome = polynomCPU;
				example.requiredTime = low->TimeValueOfX(example.polynome,example.numberOfAssignedImages);
				example.powerconsumption = example.requiredTime*powerConsumptionCPU;
				list.push_back(example);
				return list;
		}
	}
		for (std::string elem : hardware) {
		if ((elem.compare(FPGA)) == 0) {
			example.name = elem;
				example.polynome = polynomFPGA;
				example.requiredTime = low->TimeValueOfX(example.polynome,example.numberOfAssignedImages);
				example.powerconsumption = example.requiredTime*powerConsumptionFPGA;
				list.push_back(example);
				return list;
		}
		delete low;
		return list;
	}
	
	//throw "CPU needed for this type of neural network. No Batch-processing is supported";
		return list;

}
/**
 * @brief Construct a new Lowest Power Consumption:: Lowest Power Consumption object
 * 
 */
LowestPowerConsumption::LowestPowerConsumption()
{
}
/**
 * @brief same as in highestPerformance class 
 * 
 * @param polynome 
 * @param x 
 * @return double 
 */
double LowestPowerConsumption::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value = 0;
	double valuefirstpoint = 0;
	int size = polynome.size();
	double firstpoint = 0;
	double secondpoint = 0;
	int criticalsize = 100000;
	int criticalsizeHalf = (criticalsize / 2);
	if (x > criticalsize) {
		for (size_t i = 0; i < size; i++) {
			value = value + polynome.at(criticalsize) * pow(x, (size - i - 1));
			valuefirstpoint = valuefirstpoint + polynome.at(criticalsizeHalf) * pow(x, (size - i - 1));
			

		}
		std::pair<double, double> firstCoordinate = std::make_pair(criticalsize, value);
		std::pair<double, double> secondCoorinate = std::make_pair(criticalsizeHalf, valuefirstpoint);
		double a = (double)criticalsize - (double)criticalsizeHalf;
		double b = value - valuefirstpoint;
		double quotient = (b / a);
		double rest = value - (quotient * criticalsize);
		double result = value + (x - criticalsize) * quotient + rest;
		return result;

	}
	else {
		double value = 0;
		int i = 0;
		for (size_t sI = 0; sI < polynome.size(); sI++) {
			i = sI;
			int size = polynome.size();
			value = value + polynome.at(i) * pow(x, size - i - 1);
		}
		return value;
	}
}

