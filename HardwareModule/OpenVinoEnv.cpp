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
#include <chrono>
#include <vector>




OpenVinoEnv::OpenVinoEnv() {
    chooseNeuralNet("ALEXNET");
}
void OpenVinoEnv::classify() {
    cerr<<"Classify in OpenVino called"<<endl;

    this->endResultsAttribute.clear();
    try {
        readIR();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the .xml and .bin files");
        endResultsAttribute.push_back(r);
        return;
    }
    // reading and preparing images
    try {
        configureInputAndOutput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the images");
        endResultsAttribute.push_back(r);
        return;
    }
    // creating infer requests on the provided hardware platforms
    try {
        createRequestsWithInput();
    } catch (...) {
        Result r;
        r.setPath("ERROR in createRequestWithInput loading the network on the hardware plugin(s)");
        endResultsAttribute.push_back(r);
        return;
    }
    // starting classifcation
    try {
        infer();

    } catch (...) {
        Result r;
        r.setPath("ERROR infer not successfull");
        endResultsAttribute.push_back(r);
        return;
    }

    // getting output and saving results
    try {
        processOutput();

    } catch (...) {
        Result r;
        r.setPath("ERROR in processOutput");
        endResultsAttribute.clear();
        endResultsAttribute.push_back(r);
        return;
    }
}


void OpenVinoEnv::readIR()
{
    cerr<<"readIR in OpenVino called"<<endl;
    InferenceEngine::CNNNetReader network_reader;
    network_reader.ReadNetwork("Networks/"+ this->structurePath);
    network_reader.ReadWeights("Networks/" + this->weightsPath);
    this->cnnnetworkAttribute = network_reader.getNetwork();
}
void OpenVinoEnv::configureInputAndOutput()
{
    cerr<<"configureInputand Output in OpenVino called"<<endl;
    InferenceEngine::InputsDataMap input_info(cnnnetworkAttribute.getInputsInfo());
    this->inputInfoAttribute = input_info;
    auto inputInfoItem = *input_info.begin();
    inputInfoItem.second->setPrecision(InferenceEngine::Precision::U8);
    inputInfoItem.second->setLayout(InferenceEngine::Layout::NCHW);
    std::vector<std::shared_ptr<unsigned char>> imagesData = {};
        std::vector<std::string> validImageNames = {};
        cerr << "size of image Names is " << imageNamesAttribute.size() << endl;
        for (const auto & i : imageNamesAttribute) {
            FormatReader::ReaderPtr reader(i.c_str());
            if (reader.get() == nullptr) {
                std::cerr << "Image " + i + " cannot be read!" << std::endl;
                continue;
            }
            /* Store image data */
            std::shared_ptr<unsigned char> data(
                        reader->getData(inputInfoItem.second->getTensorDesc().getDims()[3],
                        inputInfoItem.second->getTensorDesc().getDims()[2]));
            if (data != nullptr) {
                imagesData.push_back(data);
                validImageNames.push_back(i);
            }
        }
        if (imagesData.empty()) throw std::logic_error("Valid input images were not found!");
        this->imagesDataAttribute = imagesData;
        this->validImageNamesAttribute = validImageNames;

    /* Setting batch size using image count */
    cnnnetworkAttribute.setBatchSize(imagesData.size());
    size_t batchSize = cnnnetworkAttribute.getBatchSize();
    std::cerr << "Batch size is " << std::to_string(batchSize) << std::endl;
    this->batchSizeAttribute = batchSize;
}

void OpenVinoEnv::createRequestsWithInput()
{
    cerr<<"createRequestWithInput in OpenVino called"<<endl;
    mutex en_mutex;
    en_mutex.lock();
    InferenceEngine::ExecutableNetwork en;
    cerr<<"Inferrequest on "<<cnnnetworkAttribute.getName()<<" on platform "<<deviceName<<" with nr of imgs "<< imagesDataAttribute.size()<<endl;
    for (int i=1; i<=20; i++) {
        try {
            en = core.LoadNetwork(cnnnetworkAttribute, deviceName);
            break;

        } catch (...) {
            cerr<<"Loading Neural Network on hardware device. Attempt number " << i << endl;
        }
        if (i ==20 ){
            throw std::logic_error("Not successful after 20 Attempts !!");
        }

    }

    en_mutex.unlock();
    InferenceEngine::InferRequest inferRequest = en.CreateInferRequest();
    for (auto & item : inputInfoAttribute) {

        InferenceEngine::Blob::Ptr inputBlob = inferRequest.GetBlob(item.first);
        InferenceEngine::SizeVector dims = inputBlob->getTensorDesc().getDims();
        /* Fill input tensor with images. First b channel, then g and r channels */
        size_t num_channels = dims[1];
        size_t image_size = dims[3] * dims[2];
        auto data = inputBlob->buffer().as<InferenceEngine::PrecisionTrait<InferenceEngine::Precision::U8>::value_type *>();
        /* Iterate over all input images */
        for (size_t image_id = 0; image_id < imagesDataAttribute.size(); ++image_id) {
            /* Iterate over all pixel in image (b,g,r) */
            for (size_t pid = 0; pid < image_size; pid++) {
                /* Iterate over all channels */
                for (size_t ch = 0; ch < num_channels; ++ch) {
                    /*          [images stride + channels stride + pixel id ] all in bytes            */
                    data[image_id * image_size * num_channels + ch * image_size + pid] = imagesDataAttribute.at(image_id).get()[pid*num_channels + ch];
                }
            }
        }
    }
    this->inferRequestAttribute = inferRequest;
}

void OpenVinoEnv::infer()
{
    cerr<<"infer in OpenVino called"<<endl;
    this->inferRequestAttribute.Infer();
}

vector<Result> OpenVinoEnv::processOutput()
{
    cerr<<"processOutput in OpenVino called"<<endl;
    InferenceEngine::OutputsDataMap output_info(cnnnetworkAttribute.getOutputsInfo());
    this->outputInfoAttribute = output_info;
    string labelFileName = "Networks/alexnetLabels.txt";
    std::vector<std::string> labels;
    std::ifstream inputFile;
    inputFile.open(labelFileName, std::ios::in);
    if (inputFile.is_open()) {
        std::string strLine;
        while (std::getline(inputFile, strLine)) {
            labels.push_back(strLine);
        }
    }
    InferenceEngine::Blob::Ptr outputBlob = this->inferRequestAttribute.GetBlob(outputInfoAttribute.begin()->first);


    ClassificationResult classificationResult(this->inferRequestAttribute.GetBlob(outputInfoAttribute.begin()->first), validImageNamesAttribute,
                                              batchSizeAttribute, 10,
                                              labels);
    classificationResult.print();
    vector<Result> r = classificationResult.getEndResults();

    cerr << "classified with " << this->structurePath << endl;

    endResultsAttribute = r;
    return r;
}

vector<Result> OpenVinoEnv::getResults()
{
    cerr<<"getResults in OpenVino called"<<endl;
    return endResultsAttribute;
}



void OpenVinoEnv::chooseNeuralNet(string nn) {
    if(nn.compare("ALEXNET") == 0)
    {
        this->structurePath = "alexnet.xml";
        this->weightsPath = "alexnet.bin";
    }
    else if(nn.compare("GOOGLENET") == 0)
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
    this->imageNamesAttribute = imageNames;
}

void OpenVinoEnv::setDevice(string device)
{
    this->deviceName = device;
}

void OpenVinoEnv::setCore(InferenceEngine::Core core) {
    this->core=core;
}
