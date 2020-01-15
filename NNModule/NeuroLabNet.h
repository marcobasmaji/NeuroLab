#include <NNModule/NeuralNet.h>


class NeuroLabNet: public NeuralNet 
{
public:
    NeuroLabNet();
	void init();
	void classify();
	void train();
	void executeTransferLearning();
};
