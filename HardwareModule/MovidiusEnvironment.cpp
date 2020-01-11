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
    // TODO : read configurations for supported devices. This is probably the place where CPU GPU etc. are controlled. 
    auto network = network_reader.getNetwork();
    this->cnnnetwork = network;

    InferenceEngine::InputsDataMap input_info(network.getInputsInfo());
    this->inputInfo = input_info;
    InferenceEngine::OutputsDataMap output_info(network.getOutputsInfo());
    this->outputInfo = output_info;

    // fourth: load Model
    auto executable_network = plugin.LoadNetwork(network, {});

    // fifth: create an infer request
    auto infer_request = executable_network.CreateInferRequest();

    // sixth: prepareInput
    // a set of images is needed
    /** Iterating over all input blobs **/
    for (auto & item : inputInfo) {
        auto input_name = item->first;
        /** Getting input blob **/
        auto input = infer_request.GetBlob(input_name);
        /** Fill input tensor with planes. First b channel, then g and r channels **/
    
    }

    // seventh : Infer
    // performance is calculated here. Need help..
    infer_request->Infer();

    // eighth : process output
    for (auto &item : output_info) {
    auto output_name = item.first;
    auto output = infer_request.GetBlob(output_name);
    {
        auto const memLocker = output->cbuffer(); // use const memory locker
        // output_buffer is valid as long as the lifetime of memLocker
        const float *output_buffer = memLocker.as<const float *>();
        /** output_buffer[] - accessing output blob data **/



}

void MovidiusEnvironment::classify() {

}

void setNeuralNet(PretrainedNN pnn) {

}

