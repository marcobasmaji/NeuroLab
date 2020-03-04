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
    chooseNeuralNet("alexnet");
}
vector<Result> OpenVinoEnv::classify() {
    readIR();
    configureInputAndOutput();
    loadModel();
    // createInferRequest();
    //prepareInput();
    infer();
    vector<Result> results = processOutput();
    return results;
}


void OpenVinoEnv::readIR()
{
    CNNNetReader network_reader;
    QString s = QString::fromStdString(structurePath);
    QFileInfo file1("../"+s);

    network_reader.ReadNetwork( file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.xml");
    network_reader.ReadWeights(file1.absolutePath().toStdString()+"/NeuroLab/HardwareModule/alexnet.bin");
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
    this->imagesData = imagesData;
    this->validImageNames = validImageNames;
    /** Setting batch size using image count **/
    cnnnetwork.setBatchSize(imagesData.size());
    size_t batchSize = cnnnetwork.getBatchSize();
    std::cout << "Batch size is " << std::to_string(batchSize) << std::endl;
    this->batchSize = batchSize;
    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;
}

void OpenVinoEnv::loadModel()
{
    size_t count = 0;
    for(auto &i : this->distribution)
    {
        InferenceEngine::ExecutableNetwork en = core.LoadNetwork(cnnnetwork,i.first);
        InferRequest inferRequest = en.CreateInferRequest();
        for (auto & item : inputInfo) {

            Blob::Ptr inputBlob = inferRequest.GetBlob(item.first);
            SizeVector dims = inputBlob->getTensorDesc().getDims();
            /** Fill input tensor with images. First b channel, then g and r channels **/
            size_t num_channels = dims[1];
            size_t image_size = dims[3] * dims[2];

            auto data = inputBlob->buffer().as<PrecisionTrait<Precision::U8>::value_type *>();
            /** Iterate over all input images **/
            for (int image_id = count; image_id < i.second; ++image_id) {
                count ++;
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
        requests.push_back(inferRequest);

    }
    qDebug()<<"hier ok"<<endl;
}

void OpenVinoEnv::createInferRequest()
{
    for(auto &item : this->execNetworks)
    {
        this->requests.push_back(item.CreateInferRequest());
    }
    InferRequest inferRequest = this->execNetwork.CreateInferRequest();
    this->inferRequest = inferRequest;
}

void OpenVinoEnv::prepareInput()
{
    // Iterate over input blobs and fill input tensors
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
}

void OpenVinoEnv::infer()
{
    //get total number of images
    size_t numOfHardware = distribution.size();
    size_t currentIterations = 0;
    std::condition_variable condVar;
    for(auto &item : requests)
    {
        item.SetCompletionCallback([&] {
            currentIterations++;
            qDebug() << currentIterations<< endl;

            if (currentIterations == numOfHardware) {
                condVar.notify_one();
            }
        });

    }
    int i= 1;
    for(auto &item : requests)
    {
        qDebug() << "Hi im request nr"  << i++<< endl;

        item.StartAsync();
    }

    std::mutex mutex;
    std::unique_lock<std::mutex> lock(mutex);
    condVar.wait(lock, [&]{ return currentIterations == numOfHardware; });
    qDebug()<<"hier auch"<<endl;
}

vector<Result> OpenVinoEnv::processOutput()
{
    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;

    Blob::Ptr outputBlob = this->requests.back().GetBlob(output_info.begin()->first);


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

void OpenVinoEnv::setDistribution(vector<pair<string, int> > platforms)
{
    if(platforms.size()<1)
    {
        cerr << "No hardware was chosen";
    }
    else
    {
        pair<string,int> a = {"CPU",3};
        pair<string,int> b = {"CPU",3};
        vector<pair<string, int> > platforms1 = {a,b};
        this->distribution = platforms1;
    }
}




