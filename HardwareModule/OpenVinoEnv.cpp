#include "OpenVinoEnv.h"
#include <QFileInfo>
#include <QDebug>
#include <iostream>
#include <fstream>
#include <vector>
#include <memory>
#include <string>
#include <map>
#include <condition_variable>
#include <mutex>
#include <Tools/common/samples/classification_results.h>


using namespace InferenceEngine;

OpenVinoEnv::OpenVinoEnv() {

}


vector<Result> OpenVinoEnv::classify() {
    qDebug()<<"classify called in openVino"<<endl; // debug: working.
    InferenceEngine::Core core;

    //std::vector<std::string> imageNames = {"/home/mo/Pictures/tennis.jpg"}; // to save image names

    qDebug()<<"openvino called "<<endl; // debug: working.
    CNNNetReader network_reader;
    QFileInfo file1("../alexnet.xml");


    network_reader.ReadNetwork( file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.xml");
    network_reader.ReadWeights(file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.bin");

    auto network = network_reader.getNetwork();
    this->cnnnetwork = network;

    InferenceEngine::InputsDataMap input_info(network.getInputsInfo());
    this->inputInfo = input_info;

    auto inputInfoItem = *inputInfo.begin();

    std::vector<std::shared_ptr<unsigned char>> imagesData = {};
    std::vector<std::string> validImageNames = {};

    for (const auto & i : imageNames) {
        FormatReader::ReaderPtr reader(i.c_str());
        if (reader.get() == nullptr) {
            std::cerr << "Image " + i + " cannot be read!" << std::endl;
            continue;
        }
        /** Store image data **/
        std::shared_ptr<unsigned char> data(
                    reader->getData(inputInfoItem.second->getTensorDesc().getDims()[3],
                    inputInfoItem.second->getTensorDesc().getDims()[2]));
        if (data != nullptr) {
            imagesData.push_back(data);
            validImageNames.push_back(i);
        }
    }
    if (imagesData.empty()) throw std::logic_error("Valid input images were not found!");
    /** Setting batch size using image count **/
    network.setBatchSize(imagesData.size());
    size_t batchSize = network.getBatchSize();
    std::cout << "Batch size is " << std::to_string(batchSize) << std::endl;

    // Load model
    auto executable_network = core.LoadNetwork(network, "CPU");

    // create Request
    std::cout << "Create infer request" << std::endl;
    InferRequest inferRequest = executable_network.CreateInferRequest();

    // prepare input
    for (auto & item : inputInfo) {
        Blob::Ptr inputBlob = inferRequest.GetBlob(item.first);
        SizeVector dims = inputBlob->getTensorDesc().getDims();
        /** Fill input tensor with images. First b channel, then g and r channels **/
        size_t num_channels = dims[1];
        size_t image_size = dims[3] * dims[2];

        auto data = inputBlob->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();
        /** Iterate over all input images **/
        for (size_t image_id = 0; image_id < imagesData.size(); ++image_id) {
            /** Iterate over all pixel in image (b,g,r) **/
            for (size_t pid = 0; pid < image_size; pid++) {
                /** Iterate over all channels **/
                for (size_t ch = 0; ch < num_channels; ++ch) {
                    /**          [images stride + channels stride + pixel id ] all in bytes            **/
                    data[image_id * image_size * num_channels + ch * image_size + pid] = imagesData.at(image_id).get()[pid*num_channels + ch];
                }
            }
        }
    }

    inferRequest.Infer();

    //process output
    InferenceEngine::OutputsDataMap output_info(network.getOutputsInfo());
    this->outputInfo = output_info;

    Blob::Ptr outputBlob = inferRequest.GetBlob(outputInfo.begin()->first);

    for (auto &item : output_info) {
        auto output_name = item.first;
        auto output = inferRequest.GetBlob(output_name);
        {
            auto const memLocker = output->cbuffer(); // use const memory locker
            // output_buffer is valid as long as the lifetime of memLocker
            const float *output_buffer = memLocker.as<const float *>();
            /** output_buffer[] - accessing output blob data **/
            QFileInfo file2("../alexnetLabels.txt");
            std::string labelFileName = file2.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnetLabels.txt";
            std::vector<std::string> labels;

            std::ifstream inputFile;
            inputFile.open(labelFileName, std::ios::in);
            if (inputFile.is_open()) {
                std::string strLine;
                while (std::getline(inputFile, strLine)) {

                    labels.push_back(strLine);
                }
            }

            ClassificationResult classificationResult(outputBlob, validImageNames,
                                                      batchSize, 10,
                                                      labels);
            classificationResult.print();
            endResults = classificationResult.getEndResults();

        }
    }

    qDebug()<<"Nr of results in vino environm. : "<< endResults.size()<<endl;
    return endResults;
}

void OpenVinoEnv::chooseNeuralNet(string nn) {
    if(nn == ("alexnet"))
    {
        this->structurePath = "alexnet.xml";
        this->weightsPath = "alexnet.bin";
    }
    else if(nn == "googlenet")
    {
        this->structurePath = "googlenet.xml";
        this->weightsPath = "googlenet.bin";

    }
    else
    {
        cerr << "invalid network";
    }

}

void OpenVinoEnv::setImageNames(std::vector<std::string> imageNames)
{
    this->imageNames = imageNames;
    //cout <<imageNames.back();
}

void OpenVinoEnv::setPlatforms(vector<string> platforms)
{
    if(platforms.size()<1)
    {
        cerr << "No hardware was chosen";
    }
    else if(platforms.size() == 1)
    {
        this->deviceName = platforms.back();
    }
    else
    {
        this->deviceName="HETERO:";
        for(auto &item:platforms)
        {
            this->deviceName += item;
        }
    }
}



