#include <MovidiusEnvironment.h>

MovidiusEnvironment::MovidiusEnvironment() {
	// do nothing
}

void MovidiusEnvironment::initMovidius() {
	// steps are taken from the link provided in the git repo. Steps can be divided in private functions
	// first  load plugin
	//TODO : what is eGPU ? what are the others called ? 
	PluginPtr engine_ptr = PluginDispatcher(pluginDirs).getSuitablePlugin(TargetDevice::eGPU);
    InferencePlugin tmp(engine_ptr);
    this->plugin = tmp;
    // second : read model IR
    CNNNetReader network_reader;
    network_reader.ReadNetwork("Model.xml"); //path needed
    network_reader.ReadWeights("Model.bin"); //path needed
    // third : conigure input and output
    auto network = network_reader.getNetwork();
    this->cnnnetwork = network;

    InferenceEngine::InputsDataMap input_info(network.getInputsInfo());
    this->inputData = input_info;
    InferenceEngine::OutputsDataMap output_info(network.getOutputsInfo());
    this->outputData = output_info;
    // later, the rest.


}

void MovidiusEnvironment::classify() {

}

void setNeuralNet(PretrainedNN pnn) {

}

