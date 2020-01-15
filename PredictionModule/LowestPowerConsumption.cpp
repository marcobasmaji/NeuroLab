#include "LowestPowerConsumption.h"
std::list<std::pair<std::string, int>>distribute(std::list<std::string>& hardware, int numberOfImages) {
	std::string sticks[] = { "Movidius1","Movidius2","Movidius3","Movidius4" };
	for (std::string movidius : sticks) {
		for (std::string elem : hardware) {
			if (elem.compare(movidius) == 0) {
				std::list<std::pair<std::string, int>> listOfHardware;
				listOfHardware.push_back(std::make_pair(elem, numberOfImages));
				return listOfHardware;
			}
		
		}
	}
	for (std::string elem : hardware) {
		if (elem.compare("CPU") == 0) {
			std::list<std::pair<std::string, int>> listOfHardware;
			listOfHardware.push_back(std::make_pair(elem, numberOfImages));
			return listOfHardware;
		}
	}
}
