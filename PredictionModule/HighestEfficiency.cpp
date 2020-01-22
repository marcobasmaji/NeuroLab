#pragma once
#include "HighestEfficiency.h"
#include <algorithm>
#include <iostream>
std::vector<Hardware>HighestEfficiency::distributeAndPredict(std::vector<std::string>& hardwares, int numberOfImages) {
	int badgesize = 1;
	int numberOfHardwareElements = 0;
	std::string movidius1 = "Movidius1";
	std::string movidius2 = "Movidius2";
	std::string movidius3 = "Movidius3";
	std::string movidius4 = "Movidius4";
	std::string FPGA = "FPGA";
	std::string CPU = "CPU";
	std::vector<double>polynomMovidius{ 1,2,3,4 };
	std::vector<double>polynomCPU{ 1,2,3,4 };
	std::vector<double>polynomFPGA{ 1,2,3,4 };
	int number = 0;
	double requiredTime = 0;
	std::string examplestring = "example";
	HighestEfficiency* hi = new HighestEfficiency;
	Hardware example{ examplestring,number,requiredTime,polynomFPGA,requiredTime };
	std::vector<Hardware> hardwarevector;
	std::vector<std::vector<Hardware>> constellations;
	double powerConsumptionMovidius = 17;

	for (std::string element : hardwares) {
		if (element.compare(movidius1) == 0) {
			Hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;

		}
		if (element.compare(movidius2) == 0) {
			Hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius3) == 0) {
			Hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius4) == 0) {
			Hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(FPGA) == 0) {
			Hardware h{ element,number,requiredTime,polynomFPGA,16 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(CPU) == 0) {
			Hardware h{ element,number,requiredTime,polynomCPU,27 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
			
		}
	}
	//inital distribution of images on the hardware elements
	for (auto element : hardwarevector) {
		element.numberOfAssignedImages = numberOfImages / numberOfHardwareElements;// welche Elemente sind noch nicht initialisiert(rest)
		double numberAssignedImages = (double)element.numberOfAssignedImages;
		element.requiredTime = hi->TimeValueOfX(element.polynome, numberAssignedImages);
	}

	//sorts after time it takes for the hardareElements to finish the tasks assigned to them
	std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
		return h1.requiredTime < h2.requiredTime;
		});
	int size = hardwarevector.size();
	std::cout << numberOfHardwareElements << " "<< size;
	int j = 0;
	int i = 0;
	for (int k = 0; k < size ; k++) {
		for (size_t sJ = 0; sJ < hardwarevector.size() + 1; sJ++) {
			j = sJ;
			std::vector<Hardware> hardwarevec = hardwarevector;
			for (size_t sI = 0; sI < hardwarevec.size() / 2; sI++) {
				i = sI;
				while (hardwarevec.at(i).requiredTime < hardwarevec.at(size - i - 1).requiredTime) {
					hardwarevec.at(i).numberOfAssignedImages = hardwarevec.at(i).numberOfAssignedImages + badgesize;
					hardwarevec.at(size - i - 1).numberOfAssignedImages = hardwarevec.at(size - 1 - i).numberOfAssignedImages - badgesize;
					double numberOfAssignedImages = (double)hardwarevec.at(i).numberOfAssignedImages;
					hardwarevec.at(i).requiredTime = hi->TimeValueOfX(hardwarevec.at(i).polynome, numberOfAssignedImages);
					double numberOfAssignedImagesEnd = hardwarevec.at(size - i - 1).numberOfAssignedImages;
					hardwarevec.at(size - i - 1).requiredTime = hi->TimeValueOfX(hardwarevec.at(size - i - 1).polynome, numberOfAssignedImagesEnd);

				}
				std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
					return h1.requiredTime < h2.requiredTime;
					});
			}
		constellations.push_back(hardwarevec);
		std::cout << "Constellation added";

		int m = 0;
		for (size_t sM = 0; sM < hardwarevector.size()-1; sM++) {
			m = sM;
			hardwarevector.at(m).numberOfAssignedImages = numberOfImages / (numberOfHardwareElements - 1);
			double numberOfAssignedImages = hardwarevector.at(m).numberOfAssignedImages;
			hardwarevector.at(m).requiredTime = hi->TimeValueOfX(hardwarevector.at(m).polynome, numberOfAssignedImages);
		}
		std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
				return h1.requiredTime < h2.requiredTime;
				});
		delete hi;
		hardwarevector.pop_back();		
		}
	}
	std::cout << hardwarevector.size();
	std::cout << constellations.size() << "Constellation size";
	//initalize

	int counterPower = 0;
	double minPower = 0;
	// A vecctor containing a pair with the totalPowerConsumption of a certain constellation of hardwareelements and their required time
	std::vector<std::pair<double, double>> powerVector;
	for (auto powerTarget : constellations) {
		double power = 0;
		for (auto powHw : powerTarget) {
			power = power + powHw.powerconsumption * powHw.requiredTime;
		}
		powerVector.push_back(std::make_pair(power,powerTarget.back().requiredTime));
	}
	//hypothesis first quotient of the powerVector is the most optimal one.

	double  minimumQuotient = powerVector.at(0).first / powerVector.at(0).second;
	//if it is not the following code runs over all pairs in the vector and updates the minimal quotient.
	//the adress of the optimal adress in the constellation is stored in the integer counterPower
	int t = 0;
	for (size_t sT = 0; sT < powerVector.size() - 1; sT++) {
		t = sT;
		if ((powerVector.at(t).first / powerVector.at(t).second) < minimumQuotient) {
			minimumQuotient = (powerVector.at(t).first / powerVector.at(t).second);
			counterPower = t;
		}
	}
	return constellations.at(counterPower);
	
}
bool HighestEfficiency::sortbytime(Hardware& a, Hardware& b)
{
	return (a.requiredTime < b.requiredTime);
}



double HighestEfficiency::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value = 0;
	int i = 0;
	for (size_t sI = 0; sI < polynome.size(); sI++) {
		i = sI;
		int size = polynome.size();
		value = value + pow(polynome.at(size-i-1), x);
	}
	return value;
}
