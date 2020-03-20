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



using namespace InferenceEngine;

OpenVinoEnv::OpenVinoEnv() {
    chooseNeuralNet("ALEXNET");
}
void OpenVinoEnv::classify() {
    this->endResults.clear();
    try {
        readIR();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the .xml and .bin files");
        endResults.push_back(r);
    }
    // reading and preparing images
    try {
        configureInputAndOutput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the images");
        endResults.push_back(r);
    }
    // creating infer requests on the provided hardware platforms
    try {
        createRequestsWithInput(); //betrifft hw
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR loading the network on the hardware plugin(s)");
        endResults.push_back(r);
    }
    // starting classifcation
    try {
        infer();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR infer not successfull");
        endResults.push_back(r);
    }

    // getting output and saving results
    endResults = processOutput();
}


void OpenVinoEnv::readIR()
{
    CNNNetReader network_reader;
    QString s = QString::fromStdString(structurePath);
    QFileInfo file1("../"+s);

    network_reader.ReadNetwork( file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/" + structurePath);
    network_reader.ReadWeights(file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/" + weightsPath);
    this->cnnnetwork = network_reader.getNetwork();
}
void OpenVinoEnv::configureInputAndOutput()
{
    InferenceEngine::InputsDataMap input_info(cnnnetwork.getInputsInfo());
    this->inputInfo = input_info;
    auto inputInfoItem = *inputInfo.begin();

    inputInfoItem.second->setPrecision(Precision::U8);
    inputInfoItem.second->setLayout(Layout::NCHW);
    std::vector<std::shared_ptr<unsigned char>> imagesData = {};
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
    InferenceEngine::ExecutableNetwork en;
    InferenceEngine::Core core;
    cerr<<"Inferrequest on "<<cnnnetwork.getName()<<" on platform "<<deviceName<<" with nr of imgs "<< imagesData.size()<<endl;
    mutex en_mutex;
    en_mutex.lock();
    en = core.LoadNetwork(cnnnetwork, deviceName);
    en_mutex.unlock();
    InferRequest inferRequest = en.CreateInferRequest();
    for (auto & item : inputInfo) {

        Blob::Ptr inputBlob = inferRequest.GetBlob(item.first);
        SizeVector dims = inputBlob->getTensorDesc().getDims();
        /* Fill input tensor with images

Mohamadℹ️, [20.03.20 12:14]
. First b channel, then g and r channels */
        size_t num_channels = dims[1];
        size_t image_size = dims[3] * dims[2];
        auto data = inputBlob->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();
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
    this->inferRequest.Infer();
}

vector<Result> OpenVinoEnv::processOutput()
{

    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;
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
    Blob::Ptr outputBlob = this->inferRequest.GetBlob(output_info.begin()->first);


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

//int OpenVinoEnv::findMinDistribution(vector<pair<string, int> > platforms) {
//    int min = platforms.front().second;
//    for(auto &platfrom: platforms)
//    {
//        if(platfrom.second <= min)
//        {
//            min = platfrom.second;
//        }
//    }
//    cerr << min<< endl;
//    return min;
//}
