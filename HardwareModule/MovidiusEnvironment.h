#include <inference_engine.hpp>


class MovidiusEnvironment {
public:
	MovidiusEnvironment();
	void initMovidius();
	void classify();
	void setNeuralNet(PretrainedNN pnn);

	list<pair<DataElement,string>> getResults() {
		return this->results;
	};

private:
	InferencePlugin plugin;
	CNNNetwork cnnnetwork;
	InputsDataMap inputData;
	OutputsDataMap outputData;
	string pathToIR;

};