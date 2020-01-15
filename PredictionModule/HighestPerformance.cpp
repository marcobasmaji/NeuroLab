#include "HighestPerformance.h"
#include "hardware.h"
#include<list>
#include <vector>
#include<math.h>
#include<algorithm>


std::list<std::pair<std::string, int>>distribute(std::list<std::string>& hardwares, int numberOfImages) {
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

	hardware example{ "example",number,requiredTime,polynomFPGA };
	std::vector<hardware> hardwarevector;
	std::vector<std::vector<hardware>> constellations;
	double powerConsumptionMovidius = 17;

	for (std::string element : hardwares) {
		if (element.compare(movidius1) == 0) {
			hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius};
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
			
		}
		if (element.compare(movidius2) == 0) {
			hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius3) == 0) {
			hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(movidius4) == 0) {
			hardware h{ element,number,requiredTime,polynomMovidius,powerConsumptionMovidius };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(FPGA) == 0) {
			hardware h{ element,number,requiredTime,polynomFPGA,16 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
		if (element.compare(CPU) == 0) {
			hardware h{ element,number,requiredTime,polynomCPU,27 };
			hardwarevector.push_back(h);
			numberOfHardwareElements++;
		}
	}
	for (auto element : hardwarevector) {
		element.numberOfAssignedImages = numberOfImages / numberOfHardwareElements;// welche Elemente sind noch nicht initialisiert(rest)
		element.requiredTime = Koordinate(element.polynome, (double)element.numberOfAssignedImages);
	}
	
	//sorts after time it takes for the hardareElements to finish the tasks assigned to them
	std::sort(hardwarevector.begin(), hardwarevector.end(), example.sortbytime);
	int size = hardwarevector.size();
	for (int k = 0; k < size - 1; k++) {
		for (int j = 0; j < hardwarevector.size() + 1; j++) {
			for (int i = 0; i < hardwarevector.size() / 2; i++) {
				while (hardwarevector.at(i).requiredTime < hardwarevector.at(size - i - 1).requiredTime) {
					hardwarevector.at(i).numberOfAssignedImages = hardwarevector.at(i).numberOfAssignedImages + badgesize;
					hardwarevector.at(size - i - 1).numberOfAssignedImages = hardwarevector.at(size - 1 - i).numberOfAssignedImages - badgesize;
					hardwarevector.at(i).requiredTime = Koordinate(hardwarevector.at(i).polynome, (double) hardwarevector.at(i).numberOfAssignedImages);
					hardwarevector.at(size - i - 1).requiredTime = Koordinate(hardwarevector.at(size - i - 1).polynome, (double) hardwarevector.at(size - i - 1).numberOfAssignedImages);

				}
				std::sort(hardwarevector.begin(), hardwarevector.end(), example.sortbytime);
			}
			constellations.push_back(hardwarevector);//wird der hier auch verändert ?
			for (int m = 0; m < hardwarevector.size(); m++) {
				hardwarevector.at(m).numberOfAssignedImages = numberOfImages / (numberOfHardwareElements - 1);
				hardwarevector.at(m).requiredTime = Koordinate(hardwarevector.at(m).polynome, (double)hardwarevector.at(m).numberOfAssignedImages);
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

	return constellations.at(counter);
	

	
	

	//verteilt Bilder um von der schlechtesten Hardware auf die beste Hardware
		
	

	

	

}

bool sortbysec(const std::pair<double, double>& a,
	const std::pair<double, double>& b)
{
	return (a.second < b.second);
}

bool sortbysecond(const std::pair<std::string, double>& a, const std::pair<std::string, double>& b) {
	return (a.second < b.second);
}



double Koordinate(std::vector<double>& polynome ,double& x){
	int value;
	for (int i = 0; i < polynome.size(); i++) {
		value = value + pow(polynome[polynome.size()- i], x);
	}
	return value;
}

