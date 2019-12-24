#include <NeuralNet.h>


class NeuroLabNet: public NeuralNet 
{
public:
	void init();
	void classify();
	void train();
	void executeTransferLearning();
};