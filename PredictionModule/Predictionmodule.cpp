
#pragma once
#include<list>
#include<iostream>
#include "Prediction.h"
#include"PredictionController.h"
#include"DataResults.h"

using namespace std;


int main()
{
    std::vector<std::string> list;
    std::string CPU = "CPU";
    std::string Movi = "Movidius1";
std::string nn = "Alexnet";
    std::string HighestP = "HighestEfficiency";
std::string HighestE = "HighestPerformance";
std::string lowestP = "LowestPowerConsumption";
    list.push_back(CPU);
    list.push_back(Movi);
    int numberOfImages = 5;
    PredictionController* n = new PredictionController;
    DataResults d = n->calculatePredictionType(list, HighestE, numberOfImages, nn);
    std::cout << d.TotalTime << "results" <<d.TotalPowerConsumption;
    
 
}


