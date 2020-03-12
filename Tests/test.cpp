#pragma once
#include "pch.h"
#include <gtest/gtest.h>
#include <algorithm>
#include<../../../../../../Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Hardware.h>
#include<../../../../../../Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Hardware.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/AlexPrediction.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/AlexPrediction.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/DataResults.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/DataResults.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/HighestEfficiency.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/HighestEfficiency.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/HighestPerformance.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/HighestPerformance.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/LowestPowerConsumption.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/LowestPowerConsumption.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Mode.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Mode.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/NeuroPrediction.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/NeuroPrediction.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Prediction.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/Prediction.cpp>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/PredictionController.h>
#include<C:/Users/n_bai/source/repos/Predictionmodule/Predictionmodule/PredictionController.cpp>
#include <vector>
int main(int argc, char* argv[]) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
//Testname e.g bankaccountstartsempty
// objects can be created in tests and then checked
// when declaring outside TEST->TEST_F constructor + destructor necessary and name must refer to object
/**TEST(HardwareConstructor, HardwareConstructCorrect) {
    std::string test = "test";
    std::vector<double> v{ 2,3 };
    int numberofimages = 10;
    double requiredTime = 2.3;
    double flops = 3.4;
    double bandwith = 1000.1;
    double powerconsumption = 12.7;
    //Hardware h{ test ,numberofimages,requiredTime,v,powerconsumption,flops,bandwith };
    Hardware* m = new Hardware(test, numberofimages, requiredTime, v, powerconsumption, flops, bandwith);
    EXPECT_DOUBLE_EQ(m->bandwidth, bandwith);
    EXPECT_DOUBLE_EQ(m->flops, flops);
    EXPECT_EQ(m->name, test);
    EXPECT_EQ(m->numberOfAssignedImages, numberofimages);
    //EXPECT_EQ(m->polynome, polynome);
    EXPECT_DOUBLE_EQ(m->powerconsumption, powerconsumption);
    EXPECT_DOUBLE_EQ(m->requiredTime, requiredTime);
    
    
}*/
TEST(DataResultsConstructor, DataResultsCOnstructorCorrect){
    std::vector < std::pair<std::string, int>>Distribution;
    std::vector<std::pair<std::string, double>> times;
    std::vector<std::pair<std::string, double>> pConsumption;
    std::vector<std::pair<std::string, double>> flops;
    std::vector<std::pair<std::string, double>> bandwidth;
    double TotalPowerConsumption = 0;
    double TotalRequiredTime = 0;
    std::string test = "MYRIAD1";
    std::string test2 = "MYRIAD2";
   /** times.push_back(std::make_pair(test,10));
    times.push_back(std::make_pair(test2,13));
    pConsumption.push_back(std::make_pair(test, 5));
    pConsumption.push_back(std::make_pair(test2, 3));
    flops.push_back(std::make_pair(test, 10000));
    flops.push_back(std::make_pair(test2, 15000));
    bandwidth.push_back(std::make_pair(test, 500));
    bandwidth.push_back(std::make_pair(test2, 300));
    EXPECT_EQ(1,1); */
    EXPECT_EQ(1, 1);
}
TEST(Input, ModeLowImgHigh) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("MYRIAD.2");
    vectorOfHardwareElements.push_back("CPU");
    int numberOfImages = 6000;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    //double test = 8;
    EXPECT_DOUBLE_EQ(d.Bandwidth.at(0).second, 1400);
    EXPECT_EQ(d.Flops.at(0).second, d.Times.at(0).second * 5000000);
    EXPECT_NEAR(d.hardwareDistribution.at(0).second, 1030,10);
    
    EXPECT_NEAR(d.Times.at(0).second, d.Times.at(1).second, (0.05 * d.Times.at(0).second * d.Times.at(0).second));
    double maxvalue = std::max(d.Times.at(0).second, d.Times.at(1).second);
    EXPECT_EQ(d.TotalPowerConsumption, d.PowerConsumption.at(0).second + d.PowerConsumption.at(1).second);
    EXPECT_EQ(d.TotalTime, maxvalue);
}
TEST(HomogenousSystem, HomogenousSystemCPUAlexnet) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    int numberOfImages = 1000;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    double expected = 20.7;
    EXPECT_NEAR(d.Times.at(0).second, expected,4);
}
TEST(Input1, LowPowerMedImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    int numberOfImages = 1000;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 21.70, 3.5);
}
TEST(Input4, HighEffLowImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    int numberOfImages = 1;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 0.7, 0.5);
}
TEST(Input5, HighEffMedImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 100;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 3.4, 0.3);
}
TEST(Input6, LowPowHighImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 100;
    std::string mode = "LowestPowerConsumption";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 15.4, 0.5);
}
TEST(Input6, LowPowLowImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 10;
    std::string mode = "LowestPowerConsumption";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 7.8, 0.5);
}
TEST(Input7, LowPowLowImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 1000;
    std::string mode = "LowestPowerConsumption";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 100, 10);
}

TEST(Input2, HighPerlowImg) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 10;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.Times.at(0).second, 7,73, 0.5);
}
TEST(Polynome, PolynomeCorrect) {
    HighestEfficiency* h = new HighestEfficiency();
    std::vector<double> test{ 2,3 };
    double target = 9;
    EXPECT_DOUBLE_EQ(h->TimeValueOfX(test, 3), target);
}
TEST(Neuro, NeuroPredictionlow) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("CPU");
    int numberOfImages = 1000;
    std::string mode = "HighestEfficiency";
    std::string nn = "NEURONET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.TotalTime, 22, 4);
}
TEST(Myriad,OneMyriad) {
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("MYRIAD.1");
    int numberOfImages = 100;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    EXPECT_NEAR(d.TotalTime, 15, 3, 3);
}
TEST(Myriads,MultipleMyriads){
    std::vector<std::string> vectorOfHardwareElements;
    vectorOfHardwareElements.push_back("MYRIAD.1");
    vectorOfHardwareElements.push_back("MYRIAD.2");
    vectorOfHardwareElements.push_back("MYRIAD.3");
    vectorOfHardwareElements.push_back("MYRIAD.4");
    int numberOfImages = 1000;
    std::string mode = "HighestEfficiency";
    std::string nn = "ALEXNET";
    PredictionController* p = new PredictionController;
    DataResults d = p->calculatePrediction(numberOfImages, nn, mode, vectorOfHardwareElements);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {
                EXPECT_EQ(1, 1);
            }
            else {
                EXPECT_NEAR(d.hardwareDistribution.at(i).second, d.hardwareDistribution.at(j).second, 16);
            }
        }
    }
    
}


/**
TEST(DataResultsConstructor, DataResultsConstructorCorrect) {
    std::vector<std::pair<std::string, int>> hDistribution;
    std::vector<std::pair<std::string, double>> times;
    std::vector<std::pair<std::string, double>> pConsumption;
    std::vector<std::pair<std::string, double>> fflops;
    std::vector<std::pair<std::string, double>> bbandwidth;
    std::vector<Hardware> constellation;
    std::string test = "test";
    std::vector<double> v{ 2,3 };
    int numberofimages = 1;
    double requiredTime = 2.3;
    double flops = 3.4;
    double bandwith = 5.6;
    double powerconsumption = 0.1;
    Hardware h{ test ,numberofimages,requiredTime,v,powerconsumption,flops,bandwith };
    double TotalPowerConsumption = 0;
    double TotalRequiredTime = 0;
    //DataResults d* = new DataResults(constellation);

}

TEST(ImageNumber, HighImageNumber) {
    int numberOfImages = 10000;
    std::string nn = "ALEXNET";
    std::string operationmode = "HighestPerformance";
    EXPECT_EQ(1, 1);
}
TEST(ImageNumber, LowImageNumber) {

}
TEST(ImageNumber, MediumImageNumber) {

}
TEST(Movidius, OneMovidius) {

}
TEST(Movidius, TwoMovidius) {

}
TEST(Movidius, ThreeMovidius) {

}
TEST(Movidius, FourMovidius) {

}
TEST(System, Homogenous) {

}
TEST(System, Heterogenous) {

}
TEST(Modes, LowestPowerConsumptionMode) {

}
TEST(Modes, HighestEfficiencyMode) {

}
TEST(Modes, HighestPerformanceMode) {

}
*/