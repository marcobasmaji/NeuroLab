#pragma once

#include <string>

using namespace std;

class ManuelTestData{
public:
    string getMaxPoolingInputValuesTest1();
    string getMaxPoolingOutputValuesTest1();
    string getMaxPoolingErrorsInputTest1();
    string getMaxPoolingErrorsOutputTest1();
    string getMaxPoolingStructureTest1();

    string getDenseInputValuesTest1();
    string getDenseOutputValuesTest1();
    string getDenseErrorsInputTest1();
    string getDenseErrorsOutputTest1();
    string getDenseStructureTest1();
    string getDenseBiasesTest1();
    string getDenseWeightsTest1();
    string getDenseNewWeightsTest1();
    string getDenseNewBiasesTest1();
    string getDenseLearningRateTest1();

    string getConvInputValuesTest1();
    string getConvOutputValuesTest1();
    string getConvErrorsInputTest1();
    string getConvErrorsOutputTest1();
    string getConvStructureTest1();
    string getConvBiasesTest1();
    string getConvWeightsTest1();
    string getConvNewBiasesTest1();
    string getConvNewWeightsTest1();
    string getConvLearningRateTest1();
};
