#include "HighestPerformance.h"
#include "hardware.h"
#include<list>
#include<math.h>
#include<algorithm>


std::vector<Hardware>Mode::distributeAndPredict(std::vector<std::string>& hardwares, int numberOfImages) {
	int badgesize = 5;
	int numberOfHardwareElements = 0;
	std::vector<std::string> hardwares; 
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

	Hardware example{examplestring,number,requiredTime,polynomFPGA,requiredTime };
	std::vector<Hardware> hardwarevector;
	std::vector<std::vector<Hardware>> constellations;
	double powerConsumptionMovidius = 17;

	for (std::string element : hardwares) {
		if (element.compare(movidius1) == 0) {
			Hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius};
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
	for (auto element : hardwarevector) {
		element.numberOfAssignedImages = numberOfImages / numberOfHardwareElements;// welche Elemente sind noch nicht initialisiert(rest)
		double numberAssignedImages = (double)element.numberOfAssignedImages;
		element.requiredTime = TimeValueOfX(element.polynome, numberAssignedImages);
	}
	
	//sorts after time it takes for the hardareElements to finish the tasks assigned to them
	std::sort(hardwarevector.begin(), hardwarevector.end(), example.sortbytime);
	int size = hardwarevector.size();
	for (int k = 0; k < size - 1; k++) {
		for (int j = 0; j < hardwarevector.size() + 1; j++) {
			std::vector<Hardware> hardwarevec = hardwarevector;
			for (int i = 0; i < hardwarevec.size() / 2; i++) {
				while (hardwarevec.at(i).requiredTime < hardwarevec.at(size - i - 1).requiredTime) {
					hardwarevec.at(i).numberOfAssignedImages = hardwarevec.at(i).numberOfAssignedImages + badgesize;
					hardwarevec.at(size - i - 1).numberOfAssignedImages = hardwarevec.at(size - 1 - i).numberOfAssignedImages - badgesize;
					double numberOfAssignedImages = (double)hardwarevec.at(i).numberOfAssignedImages;
					hardwarevec.at(i).requiredTime = TimeValueOfX(hardwarevec.at(i).polynome,numberOfAssignedImages);
					double numberOfAssignedImagesEnd = hardwarevec.at(size - i - 1).numberOfAssignedImages;
					hardwarevec.at(size - i - 1).requiredTime = TimeValueOfX(hardwarevec.at(size - i - 1).polynome, numberOfAssignedImagesEnd);

				}
				std::sort(hardwarevec.begin(), hardwarevec.end(), example.sortbytime);
			}
			constellations.push_back(hardwarevec);//wird der hier auch ver�ndert ?
			for (int m = 0; m < hardwarevector.size(); m++) {
				hardwarevector.at(m).numberOfAssignedImages = numberOfImages / (numberOfHardwareElements - 1);
				double numberOfAssignedImages = hardwarevector.at(m).numberOfAssignedImages;
				hardwarevector.at(m).requiredTime = TimeValueOfX(hardwarevector.at(m).polynome,numberOfAssignedImages);
			}
			std::sort(hardwarevector.begin(), hardwarevector.end(), example.sortbytime);
			hardwarevector.pop_back();
			// am ineffizienteste muss aussoritert werden durch neue vermutete Verteilung oder auf bestehen der alten?
		}
	}
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
	int minimumTime = constellations.at(0).back().requiredTime;
	for (auto target : constellations) {
		if (target.back().requiredTime < minimumTime) {
			minimumTime = target.back().requiredTime;
			ireturn = counter;
		}
		counter++;
	}
	std::vector<std::pair<std::string, int>> returnvalue;

	for (auto element : constellations.at(counter)) {
		std::pair<std::string, int> name = std::make_pair(element.name, element.numberOfAssignedImages);
		returnvalue.push_back(name);
	}
	return constellations.at(counter);
	

	
	

	//verteilt Bilder um von der schlechtesten Hardware auf die beste Hardware
		
	

	

	

}

HighestPerformance::HighestPerformance()
{
}

double HighestPerformance::TimeValueOfX(std::vector<double>& polynome, double x)
{
	double value;
	for (int i = 0; i < polynome.size(); i++) {
		value = value + pow(polynome[polynome.size() - i], x);
	}
	return value;
}
