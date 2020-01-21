
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
std::string nn = "Alexnet";
    std::string HighestP = "HighestPerformance";
    list.push_back(CPU);
    int numberOfImages = 5;
    PredictionController* n = new PredictionController;
    DataResults d = n->calculatePredictionType(list, HighestP, numberOfImages, nn);
    std::cout << d.TotalTime;
    
 
}


