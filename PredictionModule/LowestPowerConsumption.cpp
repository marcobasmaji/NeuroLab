
#include "LowestPowerConsumption.h"
#include <iostream>
#include <math.h>

std::vector<Hardware>LowestPowerConsumption::distributeAndPredict(std::vector<std::string>& hardware, int numberOfImages) {
	std::vector<Hardware> list;
	std::string examplestring = "example";
	double requiredTime = 0;
	std::vector<double>polynomCPU{ -0.0004,0.1462,0.785 };
	std::vector<double> polynomFPGA{ 2,3,4,5 };
	std::vector<double>polynomMovidius{ -0.0004,0.1462,0.785 };
	Hardware example{ examplestring,numberOfImages,requiredTime,polynomFPGA,requiredTime,0.0,0.0 };
	std::string CPU = "CPU";
	std::string FPGA = "FPGA";
	std::string sticks[] = { "MYRIAD.1","MYRIAD.2","MYRIAD.3","MYRIAD.4" };
	double powerConsumptionFPGA = 0;
	double powerConsumptionCPU = 0;
	double powerConsumptionMovidius = 0;
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

LowestPowerConsumption::LowestPowerConsumption()
{
}

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
			std::cout << value << "hi";

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

