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

    this->endResults.clear();
    try {
        readIR();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the .xml and .bin files");
        endResults.push_back(r);
        return;
    }
    // reading and preparing images
    try {
        configureInputAndOutput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the images");
        endResults.push_back(r);
        return;
    }
    // creating infer requests on the provided hardware platforms
    try {
        createRequestsWithInput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR loading the network on the hardware plugin(s)");
        endResults.push_back(r);
        // when plugin not loaded, the function infer() is still called. So must return.
        return;
    }
    // starting classifcation
    try {
        //mutex en_mutex;
        //en_mutex.lock();
        infer();
        //en_mutex.unlock();

    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR infer not successfull");
        endResults.push_back(r);
        return;
    }

    // getting output and saving results
    endResults = processOutput();
}


void OpenVinoEnv::readIR()
{
    cerr<<"readIR in OpenVino called"<<endl;
    InferenceEngine::CNNNetReader network_reader;
    //QString s = QString::fromStdString(structurePath);
    //QFileInfo file1("../"+s);

    // network_reader.ReadNetwork( file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/" + structurePath);
    //network_reader.ReadWeights(file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/" + weightsPath);
    network_reader.ReadNetwork("Networks/"+ this->structurePath);
    network_reader.ReadWeights("Networks/" + this->weightsPath);
    this->cnnnetwork = network_reader.getNetwork();
}
void OpenVinoEnv::configureInputAndOutput()
{
    cerr<<"configureInputand Output in OpenVino called"<<endl;
    InferenceEngine::InputsDataMap input_info(cnnnetwork.getInputsInfo());
    cerr<<"1"<<endl;
    this->inputInfo = input_info;
    cerr<<"2"<<endl;
    auto inputInfoItem = *input_info.begin();
    cerr<<"3"<<endl;

    inputInfoItem.second->setPrecision(InferenceEngine::Precision::U8);
    cerr<<"4"<<endl;
    inputInfoItem.second->setLayout(InferenceEngine::Layout::NCHW);
    cerr<<"5"<<endl;
    std::vector<std::shared_ptr<unsigned char>> imagesData = {};
    cerr<<"6"<<endl;
    std::vector<std::string> validImageNames = {};
    cerr << "size of image Names is " << imageNames.size() << endl;
    for (const auto & i : imageNames) {
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
    this->imagesData = imagesData;
    this->validImageNames = validImageNames;
    /* Setting batch size using image count */
    cnnnetwork.setBatchSize(imagesData.size());
    size_t batchSize = cnnnetwork.getBatchSize();
    std::cerr << "Batch size is " << std::to_string(batchSize) << std::endl;
    this->batchSize = batchSize;
    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;
}

void OpenVinoEnv::createRequestsWithInput()
{
    cerr<<"createRequestWithInput in OpenVino called"<<endl;
    InferenceEngine::ExecutableNetwork en;
    //    InferenceEngine::Core core;
    cerr<<"Inferrequest on "<<cnnnetwork.getName()<<" on platform "<<deviceName<<" with nr of imgs "<< imagesData.size()<<endl;
    mutex en_mutex;
    en_mutex.lock();
    en = core->LoadNetwork(cnnnetwork, deviceName);
    en_mutex.unlock();
    InferenceEngine::InferRequest inferRequest = en.CreateInferRequest();
    for (auto & item : inputInfo) {

        InferenceEngine::Blob::Ptr inputBlob = inferRequest.GetBlob(item.first);
        InferenceEngine::SizeVector dims = inputBlob->getTensorDesc().getDims();
        /* Fill input tensor with images. First b channel, then g and r channels */
        size_t num_channels = dims[1];
        size_t image_size = dims[3] * dims[2];
        auto data = inputBlob->buffer().as<InferenceEngine::PrecisionTrait<InferenceEngine::Precision::U8>::value_type *>();
        /* Iterate over all input images */
        for (size_t image_id = 0; image_id < imagesData.size(); ++image_id) {
            /* Iterate over all pixel in image (b,g,r) */
            for (size_t pid = 0; pid < image_size; pid++) {
                /* Iterate over all channels */
                for (size_t ch = 0; ch < num_channels; ++ch) {
                    /*          [images stride + channels stride + pixel id ] all in bytes            */
                    data[image_id * image_size * num_channels + ch * image_size + pid] = imagesData.at(image_id).get()[pid*num_channels + ch];
                }
            }
        }
    }
    this->inferRequest = inferRequest;
}

void OpenVinoEnv::infer()
{
    cerr<<"infer in OpenVino called"<<endl;
    this->inferRequest.Infer();
}

vector<Result> OpenVinoEnv::processOutput()
{
    cerr<<"processOutput in OpenVino called"<<endl;
    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;
    //QFileInfo file2("../alexnetLabels.txt");
    //std::string labelFileName = file2.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnetLabels.txt";
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
    InferenceEngine::Blob::Ptr outputBlob = this->inferRequest.GetBlob(output_info.begin()->first);


    ClassificationResult classificationResult(outputBlob, validImageNames,
                                              batchSize, 10,
                                              labels);
    classificationResult.print();
    vector<Result> r = classificationResult.getEndResults();


    cerr << "classified with " << this->structurePath << endl;

    return r;
}

vector<Result> OpenVinoEnv::getResults()
{
    cerr<<"getResults in OpenVino called"<<endl;
    return endResults;
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
    this->imageNames = imageNames;
}

void OpenVinoEnv::setDevice(string device)
{
    this->deviceName = device;
}

void OpenVinoEnv::setCore(InferenceEngine::Core *core) {
    this->core=core;
}
