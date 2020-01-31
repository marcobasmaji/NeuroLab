#include "NeuroLabNet.h"


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
    //this->conv1 = &conv1;
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
                    // teilen durch 255.0 und umgekehrt ?
                    pixels[(i * 105 + j) * 3 + h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                }
            }
        }
        layers.front()->getCLLayer()->setInputs(clEnv,pixels,105*105*3);
        for(auto &item:layers)
        {
            item->forwardPass(pixels,pixels);
        }
        float* prob = layers.back()->getCLLayer()->getOutputs(clEnv,10,100,1,1,nullptr);
        Result result;
        result.setPath(item);
        result.setLabelsAndProb(getLabelWithProb(prob));

        results.push_back(result);
    }
    return results;
}

void NeuroLabNet::train() {
// read image list from directory
    string labels[100] ={};
    QDir dir("/home/mo/classes");
    QStringList files = dir.entryList(QStringList(),QDir::Dirs);
    int i = 0;
    for(auto &item : files) {
        if(item.startsWith(".")){
            continue;
        }
        labels[i] = item.toStdString();
        i++;
    }
    // for each folder
    for(auto & folder : files)
    {
        // test
        cout<<folder.toStdString()<<"\n";
        QDir dirOfOmages("/home/mo/classes/"+folder);
        QStringList images = dir.entryList((QStringList()<<"*.jpg"<<"*.JPG",QDir::Files));
        for(auto & image:images)
        {
            float *pixels = getPixelsFromPath(image.toStdString());
            //this->conv1->forwardPass(pixels,nullptr);
            //this->relu1->forwardPass(pixels,nullptr);
            this->max1->forwardPass(pixels,nullptr);
            //this->conv2->forwardPass(pixels,nullptr);
            //this->relu2->forwardPass(pixels,nullptr);
            this->max2->forwardPass(pixels,nullptr);
            this->dense->forwardPass(pixels,nullptr);
            this->soft->forwardPass(pixels,nullptr);
            // compute error with Loss (using labels as well)
            float * lossOutput=lossFunction->getOutputError(this->soft->getLayerOutput(),folder.toStdString());
            // back propagate
            this->soft->backPropagate(lossOutput);
            this->dense->backPropagate(nullptr);
            this->max2->backPropagate(nullptr);
            //this->relu2->backPropagate(nullptr);
            //this->conv2->backPropagate(nullptr);
            //this->max1->backPropagate(nullptr);
            //this->relu1->backPropagate(nullptr);
            //this->conv1->backPropagate(nullptr);
            // update weights
            //this->dense->updateWeights();
            //this->conv2->updateWeights();
            //this->conv1->updateWeights();
            // save updated weights ?TODO
        }
    }

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




float* NeuroLabNet::getPixelsFromPath(string path)
{
    cv::Mat img = cv::imread(path);
    if(img.empty())
    {
        cerr<<"Image is invalid";
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
    return pixels;
}


int ReverseInt (int i)
{
    unsigned char ch1, ch2, ch3, ch4;
    ch1 = i & 255;
    ch2 = (i >> 8) & 255;
    ch3 = (i >> 16) & 255;
    ch4 = (i >> 24) & 255;
    return((int) ch1 << 24) + ((int)ch2 << 16) + ((int)ch3 << 8) + ch4;
}

void NeuroLabNet::trainWithMnist()
{
    // read Mnist
    string filename = "/home/mo/Downloads/mNIST/t10k-labels-idx3-ubyte";
    vector<cv::Mat> vec;
    ifstream file (filename, ios::binary);
        if (file.is_open())
        {
            int magic_number = 0;
            int number_of_images = 0;
            int n_rows = 0;
            int n_cols = 0;
            file.read((char*) &magic_number, sizeof(magic_number));
            magic_number = ReverseInt(magic_number);
            file.read((char*) &number_of_images,sizeof(number_of_images));
            number_of_images = ReverseInt(number_of_images);
            file.read((char*) &n_rows, sizeof(n_rows));
            n_rows = ReverseInt(n_rows);
            file.read((char*) &n_cols, sizeof(n_cols));
            n_cols = ReverseInt(n_cols);
            for(int i = 0; i < number_of_images; ++i)
            {
                cv::Mat tp = Mat::zeros(n_rows, n_cols, CV_8UC1);
                for(int r = 0; r < n_rows; ++r)
                {
                    for(int c = 0; c < n_cols; ++c)
                    {
                        unsigned char temp = 0;
                        file.read((char*) &temp, sizeof(temp));
                        tp.at<uchar>(r, c) = (int) temp;
                    }
                }
                vec.push_back(tp);
            }
        }

        //cout<<vec.size()<<endl;
        //imshow("1st", vec[5000]);
        //waitKey();

        // now train
}






