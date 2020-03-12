#pragma once
#include "HighestEfficiency.h"
//#include "../PredictionModule/Hardware.h"
#include"Hardware.h"
#include <algorithm>
#include <iostream>
#include <math.h>
/**
 * @brief Construct a new std::vector<Hardware>Highest Efficiency::distribute And Predict object main calculation method for the highest efficiency mode.
 * The goal of this method is to make a distribution of images to hardware elments where the product of Powerconsumption / second * required time is as low as possible.
 * @param hardwares a reference to a vector that contains the name of the hardware elements
 * @param numberOfImages an integer containing the number of images that need to be classified
 * @ return a vector of hardware elements that represents a optimal constellation
 */
std::vector<Hardware>HighestEfficiency::distributeAndPredict(std::vector<std::string>& hardwares, int numberOfImages) {
	int badgesize = 16;
	int numberOfHardwareElements = 0;
	std::string movidius1 = "MYRIAD.1";
	std::string movidius2 = "MYRIAD.2";
	std::string movidius3 = "MYRIAD.3";
	std::string movidius4 = "MYRIAD.4";
	std::string FPGA = "FPGA";
	std::string CPU = "CPU";
	std::vector<double>polynomCPU{ -0.0000006,0.0237,1.1126 };
	std::vector<double> polynomFPGA{ 2,3,4,5 };
	std::vector<double>polynomMovidius{ 0.00001, 0.0825, 7.0217 };
	double requiredTime = 0;
	std::string examplestring = "example";
	HighestEfficiency* hi = new HighestEfficiency;
	std::vector<Hardware> hardwarevector;
	std::vector<std::vector<Hardware>> constellations;
	double powerConsumptionMovidius = 10;
	double powerConsumptionCPU = 100;
	double bandwithMovidius = 14100;
	double flopsMovidius = 5000000;
	double bandwithCPU = 120000;
	double flopsCPU = 50000000;
	for (std::string element : hardwares) {
		if (element.compare(movidius1) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMovidius,bandwithMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;

		}
		if (element.compare(movidius2) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMovidius,bandwithMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius3) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMovidius,bandwithMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius4) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMovidius,bandwithMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(FPGA) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomFPGA,16,0.0,0.0 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(CPU) == 0) {
			Hardware h{ element,numberOfImages,requiredTime,polynomCPU,powerConsumptionCPU,flopsCPU,bandwithCPU };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
			
		}
	}
	
	for (auto i = hardwarevector.begin(); i != hardwarevector.end(); i++) {
		i->numberOfAssignedImages = numberOfImages / numberOfHardwareElements;
		i->requiredTime = hi->TimeValueOfX(i->polynome, i->numberOfAssignedImages);
		if (i->name.compare(CPU) == 0) {
			i->bandwidth = bandwithCPU;
		}
		else  {
			if ((i->name.compare(FPGA))== 0) {
			}
			else {
				i->bandwidth = 14100;
			}
		}
		
	}
	//sorts after time it takes for the hardareElements to finish the tasks assigned to them
	std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
		return h1.requiredTime < h2.requiredTime;
		});
	int size = hardwarevector.size();
	int j = 0;
	int i = 0;
	for (int k = 0; k < size ; k++) {
		for (size_t sJ = 0; sJ < hardwarevector.size() + 1; sJ++) {
		j = sJ;
		std::vector<Hardware> hardwarevec = hardwarevector;
		size = hardwarevector.size(); // CHANGED 
			for (size_t sI = 0; sI < hardwarevec.size() / 2; sI++) {
				i = sI;
				//hier statt requiredtime quotient
				
				while ((hardwarevec.at(i).requiredTime) < hardwarevec.at(size - i - 1).requiredTime) { // CHANGED
					if (hardwarevec.at(size-i-1).numberOfAssignedImages >= 16) {
						hardwarevec.at(i).numberOfAssignedImages = hardwarevec.at(i).numberOfAssignedImages + badgesize;
						hardwarevec.at(size - i - 1).numberOfAssignedImages = hardwarevec.at(size - 1 - i).numberOfAssignedImages - badgesize;
						double numberOfAssignedImages = (double)hardwarevec.at(i).numberOfAssignedImages;
						hardwarevec.at(i).requiredTime = hi->TimeValueOfX(hardwarevec.at(i).polynome, numberOfAssignedImages);
						double numberOfAssignedImagesEnd = hardwarevec.at(size - i - 1).numberOfAssignedImages;
						hardwarevec.at(size - i - 1).requiredTime = hi->TimeValueOfX(hardwarevec.at(size - i - 1).polynome, numberOfAssignedImagesEnd);
					}
					else {
						sI++;
						goto endswap;

					}
					
					
				}
				
			
			
				std::sort(hardwarevec.begin(), hardwarevec.end(), [](Hardware& h1, Hardware& h2) {
					return h1.requiredTime < h2.requiredTime;
					});
			}
		endswap:
			std::sort(hardwarevec.begin(), hardwarevec.end(), [](Hardware& h1, Hardware& h2) {
				return h1.requiredTime < h2.requiredTime;
				});
		constellations.push_back(hardwarevec);
		
		int m = 0;
		size_t check = 0;
		if (check == hardwarevec.size() - 1) {
			goto end;
		}
		else {
			for (size_t sM = 0; sM < hardwarevector.size(); sM++) {
				m = sM;
				numberOfHardwareElements = hardwarevec.size(); //changed
				hardwarevector.at(m).numberOfAssignedImages = numberOfImages / (numberOfHardwareElements - 1);
				double numberOfAssignedImagess = hardwarevector.at(m).numberOfAssignedImages;
				hardwarevector.at(m).requiredTime = hi->TimeValueOfX(hardwarevector.at(m).polynome, numberOfAssignedImagess);
				
			}
			std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
				return h1.requiredTime*h1.powerconsumption < h2.requiredTime*h2.powerconsumption;
				});
		}		
		
		hardwarevector.pop_back();		
		}
	}
end:
	delete hi;
	
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

	double  minimumQuotient = powerVector.at(0).first * powerVector.at(0).second;
	//if it is not the following code runs over all pairs in the vector and updates the minimal quotient.
	//the adress of the optimal adress in the constellation is stored in the integer counterPower
	int t = 0;
	for (size_t sT = 0; sT < powerVector.size()-1 ; sT++) {
		t = sT;
		if ((powerVector.at(t).first * powerVector.at(t).second) < minimumQuotient) {
			minimumQuotient = (powerVector.at(t).first * powerVector.at(t).second);
			counterPower = t;
		}
	}
	if (numberOfImages % constellations.at(counterPower).size() == 0) {
		return constellations.at(counterPower);
	}
	else {
		int modulo = numberOfImages % constellations.at(counterPower).size();
		constellations.at(counterPower).at(0).numberOfAssignedImages = constellations.at(counterPower).at(0).numberOfAssignedImages + modulo;
		constellations.at(counterPower).at(0).requiredTime = TimeValueOfX(constellations.at(counterPower).at(0).polynome, constellations.at(counterPower).at(0).numberOfAssignedImages);
		return constellations.at(counterPower);
	}
	
	return constellations.at(counterPower);
	
}



/**
 * @brief calculates the time it takes the hardware elements to classify the images
 * 
 * @param polynome a vector containing doubles as coefficients
 * @param x the number of images that need to be classified
 * @return double a number that contains the calculated time in seconds
 */
double HighestEfficiency::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value = 0;
	int i = 0;
	for (size_t sI = 0; sI < polynome.size(); sI++) {
		i = sI;
		int size = polynome.size();
		value = value + polynome.at(i)*pow(x, size-i-1);
	}
	return value;
}
