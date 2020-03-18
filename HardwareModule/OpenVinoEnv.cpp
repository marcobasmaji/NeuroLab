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
    setDistribution({{"HETERO:CPU,MYRIAD", imageNames.size()}});
    this->endResults.clear();
    // reading the network from the file
    try {
        readIR();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR reading the .xml and .bin files");
        vector<Result> v;
        v.push_back(r);
        return v;
    }
    // reading and preparing images
    try {
        configureInputAndOutput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        // in this case, the exceptions adds the error cause and then classifies on the HETERO plugin
        Result r;
        r.setPath("ERROR reading the images");
        //vector<Result> v;
        endResults.push_back(r);
        //return v;
        setDistribution({{"HETERO:CPU,MYRIAD", imageNames.size()}});
        return classify();
    }
    // creating infer requests on the provided hardware platforms
    try {
        CreateRequestsWithInput();
    } catch (const InferenceEngine::details::InferenceEngineException &e) {
        Result r;
        r.setPath("ERROR loading the network on the Myriad plugin(s).\nRunning classification on the other chosen hardware.\nTip:\nTry unplugging and replugging the Myriad devices. ");
        vector<Result> v;
        v.push_back(r);
        return v;
    }
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
        en = core.LoadNetwork(cnnnetwork,i.first);
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
    int i = 0;
    for(auto &item : requests)
    {
        cerr<< "Classified " << this->distribution[i].second << " images on " << distribution[i].first << endl;
        item.Infer();
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
    for(auto &reqeust : this->requests)
    {
        Blob::Ptr outputBlob = reqeust.GetBlob(output_info.begin()->first);


        ClassificationResult classificationResult(outputBlob, validImageNames,
                                                  batchSize, 10,
                                                  labels);
        classificationResult.print();
        vector<Result> r = classificationResult.getEndResults();
        for(auto & item : r)
        {
            endResults.push_back(item);
        }
    }
    cerr << "classified with " << this->structurePath << endl;
    cerr << "Printing out each Hardware combination with its number of images" << endl;
    for(auto &i:this->distribution)
    {
        cerr<< "Hardware combination: " << i.first << "  " << "Number of Images: " << i.second << endl;
    }

    return endResults;
}



void OpenVinoEnv::chooseNeuralNet(string nn) {
    if(nn == ("ALEXNET"))
    {
        this->structurePath = "alexnet.xml";
        this->weightsPath = "alexnet.bin";
    }
    else if(nn == "GOOGLENET")
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
    this->distribution.clear();
    this->requests.clear();
    if(platforms.size() ==1)
    {
        distribution.push_back(platforms.back());
    }
    else
    {
        unsigned int size = platforms.size();
        for(unsigned int h = 0; h<size-1;h++)
        {
            // Turning the distribution into hardware combinations
            int min = platforms.front().second;
            for(auto &platfrom: platforms)
            {
                if(platfrom.second <= min)
                {
                    min = platfrom.second;
                }
            }
            cerr << min<< endl;

            // create MULTI PLUGIN
            string s = "MULTI:";
            unsigned int i = 0;
            for(auto &platform : platforms)
            {
                s = s + platform.first + (i<platforms.size()-1 ? "," : "");
                i++;
            }
            distribution.push_back({s,min*platforms.size()});
            int j =0;
            for(auto &platfrom: platforms)
            {
                if(platfrom.second == min)
                {
                    platforms.erase(platforms.begin() + j);

                } else {
                    platfrom.second -=min;

                }
                j++;
            }

        }
        // push back last plugin without MULTI
        distribution.push_back(platforms.back());
    }
}

vector<pair<string, int> > OpenVinoEnv::getDistribution()
{
    return this->distribution;
}




