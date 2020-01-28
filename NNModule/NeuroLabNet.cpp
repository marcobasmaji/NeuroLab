#include "NeuroLabNet.h"
#include "Layers/ConvolutionLayer.h"
#include "Layers/ReLULayer.h"
#include "Layers/MaxPoolingLayer.h"
#include "Layers/SoftmaxLayer.h"
#include "Layers/DenseLayer.h"

using namespace cv;




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
    layers.push_back(&conv1);
    layers.push_back(&relu1);
    layers.push_back(&maxP1);
    layers.push_back(&conv2);
    layers.push_back(&relu2);
    layers.push_back(&maxP2);
    layers.push_back(&dense);
    layers.push_back(&soft);
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
        float* prob = layers.back()->getCLLayer()->getOutputs(clEnv,10,1,100,1,(int*)100);
        Result result;
        result.setPath(item);
        result.setLabelsAndProb(getLabelWithProb(prob));

        results.push_back(result);
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


vector<pair<string,float>> NeuroLabNet::getLabelWithProb(float prob[])
{
    // need to parse labels with prob. and sort it and get the top 5
    vector<pair<string,float>> vec;
    std::fstream file("/home/mo/gitNeuro/NeuroLab/DataModule/NeuroLabLabels/fine_label_names.txt");
    string line;
    int i =0;
    while(getline(file,line))
    {
        pair<string,float> pair;
        pair.first = line;
        pair.second = prob[i];
        //sort(vec.begin(),vec.end(),sortBySec);
        vec.push_back(pair);
        i++;
    }

    return vec ;

}

void NeuroLabNet::trainWithCifar100()
{
    string filename;
    filename = "/home/mo/Downloads/cifar-100-binary/train.bin";
    vector<Mat> batch;
    Mat label = Mat::zeros(1, 10000, CV_64FC1);
    //read_batch(filename, batch, label);
    ifstream file (filename, ios::binary);
    if (file.is_open())
    {
        int numOfImages = 50000;
        int rows = 32;
        int cols = 32;
        for(int i = 0; i < numOfImages; ++i){
            unsigned char tplabel = 0;

            file.read((char*) &tplabel, sizeof(tplabel));

            vector<Mat> channels;

            Mat fin_img = Mat::zeros(rows, cols, CV_8UC3);

            for(int ch = 0; ch < 3; ++ch){

                Mat tp = Mat::zeros(rows, cols, CV_8UC1);

                for(int r = 0; r < rows; ++r){

                    for(int c = 0; c < cols; ++c){

                        unsigned char temp = 0;

                        file.read((char*) &temp, sizeof(temp));

                        tp.at<uchar>(r, c) = (int) temp;

                    }

                }

                channels.push_back(tp);

            }

            merge(channels, fin_img);

            batch.push_back(fin_img);

            label.at<Vec2b>(0, i) = (double)tplabel;

            //concatenate

            int height = batch[0].rows;

            int width = batch[0].cols;

            Mat res = Mat::zeros(height * width * 3, batch.size(), CV_64FC1);

            for(int i=0; i<batch.size(); i++){

                Mat img(height, width, CV_64FC3);

                batch[i].convertTo(img, CV_64FC3);

                vector<Mat> chs;

                split(img, chs);

                for(int j = 0; j < 3; j++){

                    Mat ptmat = chs[j].reshape(0, height * width);

                    Rect roi = cv::Rect(i, j * ptmat.rows, ptmat.cols, ptmat.rows);

                    Mat subView = res(roi);

                    ptmat.copyTo(subView);

                }

            }

            divide(res, 255.0, res);


            cv::Mat mt1 = res;

            Mat trainX = Mat::zeros(1024, 50000, CV_64FC1);
            Mat trainY = Mat::zeros(1, 50000, CV_64FC1);

            Rect roi = cv::Rect(mt1.cols * 0, 0, mt1.cols, trainX.rows);

            Mat subView = trainX(roi);

            mt1.copyTo(subView);

            roi = cv::Rect(label.cols * 0, 0, label.cols, 1);

            subView = trainY(roi);

            label.copyTo(subView);



        }
    }
}






