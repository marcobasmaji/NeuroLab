#include <iostream>
#include <string.h>
#include <utility> 
#include <list> 

using namespace std;

class NeuralNet 
{
public:
	void init() = 0;
	void classify() = 0;
	void train() = 0;
	void executeTransferLearning()=0;
	void updateDataSet(DataSet dataSet) {
		this->dataSet = dataSet;
	}
	list<pair<DataElement,string>> getResults() {
		return this->results;
	}

protected:
	Loss lossFunction;
	unsigned int netID;
	list<Layer> layers;
	DataSet dataSet;
	double loss;
	double cumulativeLoss;
	double learningRate;
	unsigned int epochs;
	unsigned int batchSize;
	list<pair<DataElement,string>> results;


};
