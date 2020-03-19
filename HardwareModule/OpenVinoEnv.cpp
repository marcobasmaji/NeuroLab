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
vector<Result> OpenVinoEnv::classify() {
    this->endResults.clear();
    // reading the network from the file
    readIR();
    // reading and preparing images
    configureInputAndOutput();
    // in this case, the exceptions adds the error cause and then classifies on the HETERO plugin
    // creating infer requests on the provided hardware platforms
    CreateRequestsWithInput(); //betrifft hw
    // starting classifcation
    infer();
    // getting output
    vector<Result> results = processOutput();
    return results;
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
    std::cerr << "Batch size is " << std::to_string(batchSize) << std::endl;
    this->batchSize = batchSize;
    InferenceEngine::OutputsDataMap output_info(cnnnetwork.getOutputsInfo());
    this->outputInfo = output_info;
}

void OpenVinoEnv::CreateRequestsWithInput()
{
    size_t count = 0;
    for(auto &i : this->distribution)
    {
        InferenceEngine::ExecutableNetwork en;
        InferenceEngine::Core core;
        cerr<<"Inferrequest for "<<cnnnetwork.getName()<<" and "<<i.first<<" and "<< i.second<<endl;
        en = core.LoadNetwork(cnnnetwork, i.first);
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
    cerr << "There are " << requests.size() << " requests" << endl;
}

void OpenVinoEnv::infer()
{
    cerr<<"infer function called"<<endl;
    int i = 0;
    //    for(auto &item : requests)
    {
        cerr<< "infer: Classified " << this->distribution[i].second << " images on " << distribution[i].first << endl;
        requests.back().Infer();
        i++;
    }
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
        Blob::Ptr outputBlob = this->requests.back().GetBlob(output_info.begin()->first);


        ClassificationResult classificationResult(outputBlob, validImageNames,
                                                  batchSize, 10,
                                                  labels);
        classificationResult.print();
        vector<Result> r = classificationResult.getEndResults();


    cerr << "classified with " << this->structurePath << endl;

    return r;
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

void OpenVinoEnv::setDistribution(vector<pair<string, int> > platforms)
{
    distribution.push_back(platforms.back());
}

vector<pair<string, int> > OpenVinoEnv::getDistribution()
{
    return this->distribution;
}

int OpenVinoEnv::findMinDistribution(vector<pair<string, int> > platforms) {
    int min = platforms.front().second;
    for(auto &platfrom: platforms)
    {
        if(platfrom.second <= min)
        {
            min = platfrom.second;
        }
    }
    cerr << min<< endl;
    return min;
}




