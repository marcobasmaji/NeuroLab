
#pragma once
#include<list>
#include<iostream>
#include "Prediction.h"

using namespace std;


int main()
{
    list<string> stringlist = {};
    
    stringlist.push_back("HI");
    string elem = "Movidius1";
    string name = "Movidius1";
    if (((elem.compare("Movidius1")) && (elem.compare("Movidius2")) && (elem.compare("Movidius3")) && (elem.compare("Movidius4")) )) {
        cout << "true";
    }
    else {
        cout << "false";
    }
   // Prediction p(3, stringlist, "lowestPowerConsumption");
    //cout << p.getTotalSeconds();
 
}


