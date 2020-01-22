#include <iostream>
#include <string.h>
#include <utility> 
#include <list> 
#include "Layers/Layer.h"
//#include "Loss.h"

using namespace std;

class NeuralNet 
{
public:
    virtual void init() = 0;
    virtual void classify() = 0;
    virtual void train() = 0;
    virtual void executeTransferLearning()=0;
    /*void updateDataSet(DataSet dataSet) {
		this->dataSet = dataSet;
	}
	list<pair<DataElement,string>> getResults() {
		return this->results;
    }*/

protected:
    //Loss lossFunction;
	unsigned int netID;
    list<Layer> layers;
    //DataSet dataSet;
	double loss;
	double cumulativeLoss;
	double learningRate;
	unsigned int epochs;
	unsigned int batchSize;
    //list<pair<DataElement,string>> results;


};
