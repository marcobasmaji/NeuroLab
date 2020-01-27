#include "NeuroLabNet.h"
#include "Layers/ConvolutionLayer.h"
#include "Layers/ReLULayer.h"
#include "Layers/MaxPoolingLayer.h"
#include "Layers/SoftmaxLayer.h"
#include "Layers/DenseLayer.h"




// constuctor
NeuroLabNet::NeuroLabNet(){
    OpenCLEnvironmentCreator* clCreator = new OpenCLEnvironmentCreator();
    //HardwareType type = HardwareType::CPU;
    OpenCLEnvironment* env = clCreator->createOpenCLEnvironment(HardwareType::CPU);
    clEnv = env;

}

void NeuroLabNet::init() {
    // the division (imageSize-filterSize)/stride must be an integer
    // image input is i.e. 105x105x3 so output image is (106- filterHeight)/ stride +1 with depth = numFilters.
    // so i chose (105 - 6) / 3 +1 = 34
    // and 50 filters
    /* ConvolutionLayer conv1(clEnv,105,105,3,6,6,3,3,50);
     // now the non linear function
     ReLULayer relu1(clEnv,34,34,50);
     MaxPoolingLayer maxP1(clEnv,34,34,50,2,2,2,2);
     // output is (34 -2) / 2 + 1 = 17
     ConvolutionLayer conv2(clEnv,17,17,50,3,3,2,2,100);
     // output is (17-3) / 2 +1 = 8 , -> 8x8x100
     ReLULayer relu2(clEnv,8,8,100);
     MaxPoolingLayer maxP2(clEnv,8,8,100,2,2,2,2);
     // output is (8-2)/2 +1 = 4
     // 4x4x100
     DenseLayer dense(clEnv,4,4,100,100);
     // output is an array with the length 100
     SoftmaxLayer soft(clEnv,100);
     //Loss loss(100);*/
    ConvolutionLayer conv1(clEnv,32,32,3,5,5,1,1,20);
    //output is (32-5)/1 +1 = 28
    // now the non linear function
    ReLULayer relu1(clEnv,28,28,20);
    MaxPoolingLayer maxP1(clEnv,28,28,20,2,2,2,2);
    // output is (28 -2) / 2 + 1 = 14
    ConvolutionLayer conv2(clEnv,14,14,20,3,3,1,1,40);
    // output is (14-3) / 1 +1 = 12 , -> 12x12x40
    ReLULayer relu2(clEnv,12,12,40);
    MaxPoolingLayer maxP2(clEnv,12,12,40,2,2,2,2);
    // output is (12-2)/2 +1 = 6
    // 6x6x40
    DenseLayer dense(clEnv,6,6,40,100);
    // output is an array with the length 100
    SoftmaxLayer soft(clEnv,100);
    //Loss loss(100)
    layers.push_front(&conv1);
    layers.push_front(&relu1);
    layers.push_front(&maxP1);
    layers.push_front(&conv2);
    layers.push_front(&relu2);
    layers.push_front(&maxP2);
    layers.push_front(&dense);
    layers.push_front(&soft);
    // init first layer

    // connect layers
    relu1.getCLLayer()->setPreviousOpenCLLayer(conv1.getCLLayer());
    maxP1.getCLLayer()->setPreviousOpenCLLayer(relu1.getCLLayer());
    conv2.getCLLayer()->setPreviousOpenCLLayer(maxP1.getCLLayer());
    relu2.getCLLayer()->setPreviousOpenCLLayer(conv2.getCLLayer());
    maxP2.getCLLayer()->setPreviousOpenCLLayer(relu2.getCLLayer());
    dense.getCLLayer()->setPreviousOpenCLLayer(maxP2.getCLLayer());
    soft.getCLLayer()->setPreviousOpenCLLayer(dense.getCLLayer());
    //this->lossFunction = loss;
}

vector<Result> NeuroLabNet::classify() {
    vector<Result> results;
    // for each image, read, resize and turn into a 3D array of pixels
    for(auto &item:dataSet)
    {
        cv::Mat img = cv::imread(item);
        if(img.empty())
        {
            cerr<<"Image is invalid";
            continue;
        }
        if(img.channels()!=3)
        {
            cerr<<"Image doesn't have enough channels";
        }
        cv::Mat resizedImg;
        cv::Size size(105,105);
        // resize image
        cv::resize(img,resizedImg,size,cv::INTER_LINEAR);
        // a 3D array of type float to save pixel values
        //float pixels[105][105][3]={};
        float pixels[105*105*3];

        for(unsigned int i =0;i<105;i++)
        {
            for(unsigned int j =0;j<105;j++)
            {
                for(unsigned int h =0;h<3;h++)
                {
                    // the function at returns an array with the length 3, whereby each field has the red, blue or green value
                    //pixels[i][j][h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                    pixels[(i * 105 + j) * 3 + h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                }
            }
        }
        layers.back()->getCLLayer()->setInputs(clEnv,pixels,105*105*3);
        for(auto &item:layers)
        {
            item->forwardPass(pixels,pixels);
        }
        layers.front()->getCLLayer()->getOutputs(clEnv,10,1,100,1,(int*)100);
        //results.push_back();
    }
    return results;


}

void NeuroLabNet::train() {
    // here foward then backward

}

void NeuroLabNet::executeTransferLearning() {
    // no idea .. yet

}

void NeuroLabNet::updateDataSet(vector<string> dataSet)
{
    this->dataSet = dataSet;
}

void NeuroLabNet::trainWithCifar100()
{

}

