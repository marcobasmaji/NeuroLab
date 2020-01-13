#include <inference_engine.hpp>


class MovidiusEnvironment {
public:
	MovidiusEnvironment();
	void initMovidius();
	void classify();
    //void setNeuralNet(PretrainedNN pnn);

    //list<pair<DataElement,string>> getResults() {
        //return this->results;
    //};

private:
    InferenceEngine::Core core;
    InferenceEngine::InferencePlugin plugin;
    //CNNNetwork cnnnetwork;
    //InputsDataMap inputInfo;
    //OutputsDataMap outputInfo;
    //string pathToIR;

};
