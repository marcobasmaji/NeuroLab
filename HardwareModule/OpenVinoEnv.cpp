#include "OpenVinoEnv.h"
#include <QFileInfo>
#include <QDebug>
using namespace InferenceEngine;

OpenVinoEnv::OpenVinoEnv() {
    qDebug()<<"openvino called "<<endl; // debug: working.
    CNNNetReader network_reader;
    QFileInfo file1("../alexnet.xml");


    network_reader.ReadNetwork( file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.xml");
    network_reader.ReadWeights(file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.bin");

    auto network = network_reader.getNetwork();
    this->cnnnetwork = network;

    InferenceEngine::InputsDataMap input_info(network.getInputsInfo());
    this->inputInfo = input_info;
    InferenceEngine::OutputsDataMap output_info(network.getOutputsInfo());
    this->outputInfo = output_info;

    for (auto &item : input_info) {
        auto input_data = item.second;
        input_data->setPrecision(Precision::U8);
        input_data->setLayout(Layout::NCHW);
        input_data->getPreProcess().setResizeAlgorithm(RESIZE_BILINEAR);
        input_data->getPreProcess().setColorFormat(ColorFormat::RGB);
    }
    /** Iterating over all output info**/
    for (auto &item : output_info) {
        auto output_data = item.second;
        output_data->setPrecision(Precision::FP32);
        output_data->setLayout(Layout::NC);
    }

    auto executable_network = core.LoadNetwork(network, "CPU");

    auto infer_request = executable_network.CreateInferRequest();
    for (auto & item : inputInfo) {
        auto input_name = item.first;
        /** Getting input blob **/
        auto input = infer_request.GetBlob(input_name);
        /** Fill input tensor with planes. First b channel, then g and r channels **/

    }
    infer_request.StartAsync();
    infer_request.Wait(IInferRequest::WaitMode::RESULT_READY);

    for (auto &item : output_info) {
        auto output_name = item.first;
        auto output = infer_request.GetBlob(output_name);
        {
            auto const memLocker = output->cbuffer(); // use const memory locker
            // output_buffer is valid as long as the lifetime of memLocker
            const float *output_buffer = memLocker.as<const float *>();
            /** output_buffer[] - accessing output blob data **/
            printf("/d",output_buffer[0]);


}
    }
}

void OpenVinoEnv::classify() {
    qDebug()<<"classify called in openVino"<<endl; // debug: working.
}
void OpenVinoEnv::initMovidius() {

}
/*void OpenVinoEnv::initMovidius() {
    // steps are taken from the link provided in the git repo. Steps can be divided in private functions
    // first  load plugin
    //TODO : what is eGPU ? what are the others called ?
    //PluginPtr engine_ptr = PluginDispatcher(pluginDirs).getSuitablePlugin(TargetDevice::eGPU);
    //InferencePlugin tmp(engine_ptr);
    //this->plugin = tmp;
    InferenceEngine::Core core;
    // second : read model IR
    CNNNetReader network_reader;
    network_reader.ReadNetwork("~/AlexNetModel/alexnet.xml");
    network_reader.ReadWeights("~/AlexNetModel/alexnet.bin");
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
    // Iterating over all input blobs
    for (auto & item : inputInfo) {
        auto input_name = item.first;
        // Getting input blob
        auto input = infer_request.GetBlob(input_name);
        // Fill input tensor with planes. First b channel, then g and r channels

    }

    // seventh : Infer
    // performance is calculated here. Need help..
    infer_request.Infer();

    // eighth : process output
    for (auto &item : output_info) {
    auto output_name = item.first;
    auto output = infer_request.GetBlob(output_name);

        auto const memLocker = output->cbuffer(); // use const memory locker
        // output_buffer is valid as long as the lifetime of memLocker
        const float *output_buffer = memLocker.as<const float *>();
        // output_buffer[] - accessing output blob data
    }
}*/



//void setNeuralNet(PretrainedNN pnn) {

//}



