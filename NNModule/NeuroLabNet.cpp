#include "NeuroLabNet.h"
#include <QDebug>


using namespace cv;


// constuctor, maybe pass a string indicating which variant of the net (5 classes or 100)
NeuroLabNet::NeuroLabNet(){
    OpenCLEnvironmentCreator* clCreator = new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env = clCreator->createOpenCLEnvironment(HardwareType::CPU);
    clEnv = env;

}

void NeuroLabNet::init() {
    // the division (imageSize-filterSize)/stride must be an integer
    // image input is 82x82x3
    // first convolution layer has a 7x7 filter size and 3 as a stride with 15 filters
    this->conv1 = new ConvolutionLayer(clEnv,82,82,3,7,7,3,3,15);
    // (82-7)/3 + 1 = 26
    // now the non linear function
    this->relu1 = new ReLULayer(clEnv,26,26,15);
    this->max1 = new MaxPoolingLayer(clEnv,26,26,15,2,2,2,2);
    // output is 13x13x15
    // second convolution layer has a 3x3 filter size and 3 as a stride with 15 filters
    this->conv2 = new ConvolutionLayer(clEnv,13,13,15,4,4,1,1,40);
    // output is (13 -4) / 1 + 1 = 10
    this->relu2 = new ReLULayer(clEnv,10,10,40);
    this->max2 = new MaxPoolingLayer(clEnv,10,10,40,2,2,2,2);
    // output is (10-2)/2 +1 = 5
    // 5x5x40
    this->dense = new DenseLayer(clEnv,5,5,40,6);
    // output is an array with the length 6
    this->soft = new SoftmaxLayer(clEnv,6);
    this -> lossFunction = new Loss(6);

    // connect layers
    relu1->getCLLayer()->setPreviousOpenCLLayer(conv1->getCLLayer());
    max1->getCLLayer()->setPreviousOpenCLLayer(relu1->getCLLayer());
    conv2->getCLLayer()->setPreviousOpenCLLayer(max1->getCLLayer());
    relu2->getCLLayer()->setPreviousOpenCLLayer(conv2->getCLLayer());
    max2->getCLLayer()->setPreviousOpenCLLayer(relu2->getCLLayer());
    dense->getCLLayer()->setPreviousOpenCLLayer(max2->getCLLayer());
    soft->getCLLayer()->setPreviousOpenCLLayer(dense->getCLLayer());
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
        cv::Size size(82,82);
        // resize image
        cv::resize(img,resizedImg,size,cv::INTER_LINEAR);
        // a 3D array of type float to save pixel values
        //float pixels[105][105][3]={};
        float pixels[82*82*3];

        for(unsigned int i =0;i<82;i++)
        {
            for(unsigned int j =0;j<82;j++)
            {
                for(unsigned int h =0;h<3;h++)
                {
                    // the function at returns an array with the length 3, whereby each field has the red, blue or green value
                    // umgekehrt?
                    pixels[(i * 105 + j) * 3 + h] = resizedImg.at<cv::Vec3b>(i,j).val[h]/255.0;
                }
            }
        }
        this->conv1->getCLLayer()->setInputs(clEnv,pixels,82*82*3);
        //layers.front()->getCLLayer()->setInputs(clEnv,pixels,82*82*3);
        /*for(auto &item:layers)
        {
            item->forwardPass(pixels,pixels);
        }*/
        this->conv1->forwardPass();
        this->relu1->forwardPass();
        this->max1->forwardPass();
        this->conv2->forwardPass();
        this->relu2->forwardPass();
        this->max2->forwardPass();
        this->dense->forwardPass();
        this->soft->forwardPass();

        float* prob = this->soft->getCLLayer()->getOutputs(clEnv,16,6,1,1,nullptr);
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
    unsigned int labelCount = 0;
    for(auto & folder : files)
    {
        labelCount++;
        qDebug()<<"#### Training with label "<< folder.toUpper() << endl;
        // test
        cout<<folder.toStdString()<<"\n";
        QDir dirOfOmages("/home/mo/classes/"+folder);
        QStringList images = dir.entryList((QStringList()<<"*.jpg"<<"*.JPG",QDir::Files));
        unsigned int count = 0;
        for(auto & image:images)
        {
            count++;
            qDebug()<<"Training with image Nr. "<< count << endl;
            // get pixels from path
            cv::Mat img = cv::imread(image.toStdString());
            if(img.empty())
            {
                cerr<<"Image is invalid";
            }
            if(img.channels()!=3)
            {
                cerr<<"Image doesn't have enough channels";
            }
            cv::Mat resizedImg;
            cv::Size size(82,82);
            // resize image
            cv::resize(img,resizedImg,size,cv::INTER_LINEAR);
            // a 3D array of type float to save pixel values
            //float pixels[105][105][3]={};
            float pixels[82*82*3];

            for(unsigned int i =0;i<82;i++)
            {
                for(unsigned int j =0;j<82;j++)
                {
                    for(unsigned int h =0;h<3;h++)
                    {
                        // the function at returns an array with the length 3, whereby each field has the red, blue or green value
                        //pixels[i][j][h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                        pixels[(i * 105 + j) * 3 + h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                    }
                }
            }
            this->conv1->getCLLayer()->setInputs(clEnv,pixels,82*82*3);
            this->conv1->forwardPass();
            this->relu1->forwardPass();
            this->max1->forwardPass();
            this->conv2->forwardPass();
            this->relu2->forwardPass();
            this->max2->forwardPass();
            this->dense->forwardPass();
            this->soft->forwardPass();
            // compute error with Loss (using labels as well)
            float * lossOutput=lossFunction->getOutputError(this->soft->getLayerOutput(),folder.toStdString());
            // back propagate
            this->soft->getCLLayer()->setOutputErrors(clEnv,lossOutput,6);
            this->soft->backPropagate();
            this->dense->backPropagate();
            this->max2->backPropagate();
            this->relu2->backPropagate();
            this->conv2->backPropagate();
            this->max1->backPropagate();
            this->relu1->backPropagate();
            this->conv1->backPropagate();
            // update weights
            this->dense->updateWeights();
            this->conv2->updateWeights();
            this->conv1->updateWeights();
            // save updated weights ?TODO
            float* weightsConv1;
            this->conv1->getCLLayer()->getWeights(clEnv,10);
            this->conv2->getCLLayer()->getWeights(clEnv,10);
            this->dense->getCLLayer()->getWeights(clEnv,10);

        }
    }
    qDebug()<<"Saving weights and biases"<< endl;

}

void NeuroLabNet::executeTransferLearning() {
    // TODO

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
        vec.push_back(pair);
        i++;
    }
    //sort(vec.begin(),vec.end(),sortBySec);
    return vec ;

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
    string filename = "/home/mo/Downloads/mNIST/t10k-images-idx3-ubyte";
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

    cout<<vec.size()<<endl;
    //imshow("1st", vec[0]);
    //waitKey();

    // start training
    // create Layers
    ConvolutionLayer conv1(clEnv,28,28,1,5,5,1,1,6);
    ReLULayer relu1(clEnv,24,24,6);
    MaxPoolingLayer maxP1(clEnv,24,24,6,2,2,2,2);
    ConvolutionLayer conv2(clEnv,12,12,6,5,5,1,1,16);
    ReLULayer relu2(clEnv,8,8,16);
    MaxPoolingLayer maxP2(clEnv,8,8,16,2,2,2,2);
    DenseLayer dense(clEnv,4,4,16,10);
    SoftmaxLayer soft(clEnv,10);
    Loss lossFunc(10);

    double loss = 0.0;
    double cumLoss = 0.0;

    for (size_t epoch = 0; epoch < 10; epoch++)
    {


        for(auto &data:vec){

            // read image
            float pixels[28*28*3];
            for(unsigned int h =0;h<3;h++)
            {
                for(unsigned int j =0;j<28;j++)
                {
                    for(unsigned int i =0;i<28;i++)
                    {
                        // the function at returns an array with the length 3, whereby each field has the red, blue or green value
                        //pixels[i][j][h] = resizedImg.at<cv::Vec3b>(i,j).val[h];
                        // teilen durch 255.0 und umgekehrt ?
                        pixels[(i * 105 + j) * 3 + h] = data.at<cv::Vec3b>(i,j).val[h];
                    }
                }
            }
            conv1.getCLLayer()->setInputs(clEnv,pixels,28*28*1);
            // forward
            conv1.forwardPass();
            relu1.forwardPass();
            maxP1.forwardPass();
            conv2.forwardPass();
            relu2.forwardPass();
            maxP2.forwardPass();
            dense.forwardPass();
            soft.forwardPass();

            // compute loss
            lossFunc.getOutputError(soft.getLayerOutput(),"");// missing label

            float* prob = soft.getCLLayer()->getOutputs(clEnv,10,100,1,1,nullptr);

        }
    }




}

