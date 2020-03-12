#pragma once
#include "HighestPerformance.h"
#include "Hardware.h"
//#include "../PredictionModule/Hardware.h"
#include<list>
#include<math.h>
#include<algorithm>
#include <iostream>

/**
 * @brief Construct a new std::vector<Hardware>Mode::distribute And Predict object 
 * This method returns a vector of hardware elements which represent a optimal constellation. Meaning that each hardware element in it has an integer with the number of images assigned to it as attribute-.
 * These images distributed in a way that the overall classification is done in as little time as possible
 * @param hardwares a reference to a vector of strings that contain the name of the chosen hardware elements
 * @param numberOfImages  an integer that contains the number of images that the user wants to classify
 */
std::vector<Hardware>HighestPerformance::distributeAndPredict(std::vector<std::string>& hardwares, int numberOfImages) {
	int badgesize = 16;
	int numberOfHardwareElements = 0;
	std::string movidius1 = "MYRIAD.1";
	std::string movidius2 = "MYRIAD.2";
	std::string movidius3 = "MYRIAD.3";
	std::string movidius4 = "MYRIAD.4";
	std::string FPGA = "FPGA";
	std::string CPU = "CPU";
	std::string GPU = "GPU";
	std::vector<double>polynomMovidius{0.00001, 0.0825, 7.0217 }; // //  0.087,6.904 linear
	std::vector<double>polynomCPU{ -0.0000006,0.0237,1.1126 };// // 0.0222, 1.2587
	std::vector<double>polynomFPGA{ 0.001,0.2,0.3,0.04 };
	int number = 0;
	double requiredTime = 0;
	std::string examplestring = "example";
	double bandwithmovidius = 14100;
	double flopsMvoidius = 5000000;
	double bandwithCPU = 120000;
	double flopsCPU = 50000000;
	Hardware example{examplestring,number,requiredTime,polynomFPGA,requiredTime,flopsCPU,bandwithCPU};
	std::vector<Hardware> hardwarevector;
	std::vector<std::vector<Hardware>> constellations;
	double powerConsumptionMovidius = 10;
	HighestPerformance* hi = new HighestPerformance;
	int desiredHardwaresize = hardwares.size();
	for (int i = 0; i < desiredHardwaresize; i++) {
		if (hardwares.at(i).compare(movidius1) == 0) {
			Hardware h{ hardwares.at(i),numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMvoidius,bandwithmovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
			
		}
		if (hardwares.at(i).compare(movidius2) == 0) {
			Hardware h{ movidius2,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMvoidius,bandwithmovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (hardwares.at(i).compare(movidius3) == 0) {
			Hardware h{ movidius3,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMvoidius,bandwithmovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (hardwares.at(i).compare(movidius4) == 0) {
			Hardware h{ movidius4,numberOfImages,requiredTime,polynomMovidius,powerConsumptionMovidius,flopsMvoidius,bandwithmovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (hardwares.at(i).compare(FPGA) == 0) {
			Hardware h{ hardwares.at(i),numberOfImages,requiredTime,polynomFPGA,1600,1000000.0,1500.0 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (hardwares.at(i).compare(CPU) == 0) {
			Hardware h{ CPU,numberOfImages,requiredTime,polynomCPU,145,flopsCPU,bandwithCPU };
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
		else {
			if ((i->name.compare(FPGA)) == 0) {
			}
			else {
				i->bandwidth = 14100;
			}
		}
	}// rest noch nicht initialisiert
	
	//sorts after time it takes for the hardareElements to finish the tasks assigned to them
	std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
		return h1.requiredTime < h2.requiredTime;
		});
	int size = hardwarevector.size();
	for (int k = 0; k < size; k++){ 
		for (size_t j = 0; j < hardwarevector.size() + 1; j++) {
			size = hardwarevector.size(); // CHANGED 
			std::vector<Hardware> hardwarevec = hardwarevector;
			for (size_t m = 0; m < hardwarevec.size(); m++) {
				for (size_t i = 0; i < hardwarevec.size() / 2; i++) {

					while (hardwarevec.at(i).requiredTime < hardwarevec.at(size - i - 1).requiredTime) {
						hardwarevec.at(i).numberOfAssignedImages = hardwarevec.at(i).numberOfAssignedImages + badgesize;
						hardwarevec.at(size - i - 1).numberOfAssignedImages = hardwarevec.at(size - 1 - i).numberOfAssignedImages - badgesize;
						double numberOfAssignedImages = (double)hardwarevec.at(i).numberOfAssignedImages;
						hardwarevec.at(i).requiredTime = hi->TimeValueOfX(hardwarevec.at(i).polynome, numberOfAssignedImages);
						double numberOfAssignedImagesEnd = hardwarevec.at(size - i - 1).numberOfAssignedImages;
						hardwarevec.at(size - i - 1).requiredTime = hi->TimeValueOfX(hardwarevec.at(size - i - 1).polynome, numberOfAssignedImagesEnd);
					}
					std::sort(hardwarevec.begin(), hardwarevec.end(), [](Hardware& h1, Hardware& h2) {
						return h1.requiredTime < h2.requiredTime;
						});
				}
			}	
		size_t check = 0;
		constellations.push_back(hardwarevec);//wird der hier auch ver�ndert ? darf eigentlich erst später kommen 
		if (check == hardwarevec.size() - 1) {
			goto end;
		}
		else {
			// oder hier nach geringstem produkt sortieren ?? TODO
			for (size_t m = 0; m < hardwarevector.size() - 1; m++) {
				numberOfHardwareElements = hardwarevec.size(); //changed
				hardwarevector.at(m).numberOfAssignedImages = numberOfImages / (numberOfHardwareElements - 1);
				double numberOfAssignedImages = hardwarevector.at(m).numberOfAssignedImages;
				hardwarevector.at(m).requiredTime = hi->TimeValueOfX(hardwarevector.at(m).polynome, numberOfAssignedImages);
			}
			std::sort(hardwarevector.begin(), hardwarevector.end(), [](Hardware& h1, Hardware& h2) {
				return h1.requiredTime < h2.requiredTime;
				});
		}

			
			hardwarevector.pop_back();
			// am ineffizienteste muss aussoritert werden durch neue vermutete Verteilung oder auf bestehen der alten?
		}
	}
end:	
	int counterPower = 0;
	double minPower = 0;
	std::vector<std::pair<double,double>> powerVector;
	/*for (auto powerTarget : constellations) {
		double power = 0;
		for (auto powHw : powerTarget) {
			power = power + powHw.powerconsumption * powHw.requiredTime;
		}
		powerVector.push_back(std::make_pair(power,powerTarget.back().requiredTime));
	}
	double  minimumQuotient = powerVector.at(0).first / powerVector.at(0).second;
	for (int i = 0; i < powerVector.size() - 1; i++) {
		if ((powerVector.at(i).first / powerVector.at(i).second) < minimumQuotient) {
			minimumQuotient = (powerVector.at(i).first / powerVector.at(i).second);
			counterPower = i;
		}
	}
	return constellations.at(counterPower);*/
	int counter = 0;
	int ireturn = 0;
	double minimumTime = constellations.at(0).back().requiredTime;
	for (auto target : constellations) {
		if (target.back().requiredTime < minimumTime) {
			minimumTime = target.back().requiredTime;
			ireturn = counter;
		}
		counter++;
	}
	
	if (numberOfImages % constellations.at(ireturn).size() == 0) {
		return constellations.at(ireturn);
	}
	else {
		int modulo = numberOfImages % constellations.at(ireturn).size();
		constellations.at(ireturn).at(0).numberOfAssignedImages = constellations.at(ireturn).at(0).numberOfAssignedImages + modulo;
		constellations.at(ireturn).at(0).requiredTime = TimeValueOfX(constellations.at(ireturn).at(0).polynome, constellations.at(ireturn).at(0).numberOfAssignedImages);
		return constellations.at(ireturn);
	}
	delete hi;
	return constellations.at(ireturn);
	

	
	

	//verteilt Bilder um von der schlechtesten Hardware auf die beste Hardware
		
	

	

	

}

HighestPerformance::HighestPerformance()
{
}

double HighestPerformance::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value = 0;
	int i = 0;
	for (size_t sI = 0; sI < polynome.size(); sI++) {
		i = sI;
		int size = polynome.size();
		value = value + polynome.at(i) * pow(x, size - i - 1);
	}
	return value;
}
