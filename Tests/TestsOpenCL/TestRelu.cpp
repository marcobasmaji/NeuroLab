#include "Tests/TestsOpenCL/TestRelu.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"

using namespace std;

#define TEST_CASES 1;

//Convolutional Layer
#define CONVOlUTIONAL_RELU_LAYER_MAX_BATCH_SIZE 10;
#define CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_HEIGHT 30;
#define CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_WIDTH 30;
#define CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_MAPS 10;
#define CONVOlUTIONAL_RELU_LAYER_MAX_OUTPUT_MAPS 10;
#define CONVOlUTIONAL_RELU_LAYER_MAX_KERNEL_HEIGHT 8;
#define CONVOlUTIONAL_RELU_LAYER_MAX_KERNEL_WIDTH 8;
#define CONVOlUTIONAL_RELU_LAYER_MAX_STRIDE_HEIGHT 8;
#define CONVOlUTIONAL_RELU_LAYER_MAX_STRIDE_WIDTH 8;
#define CONVOlUTIONAL_RELU_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestRelu::createRandomConvReluLayerCont(ConvReluLayerCont* convReluLayerCont){
    //create parameters
    int maxBatchSize=CONVOlUTIONAL_RELU_LAYER_MAX_BATCH_SIZE;
    int maxInputHeight=CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_HEIGHT;
    int maxInputWidth=CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_WIDTH;
    int maxInputMaps=CONVOlUTIONAL_RELU_LAYER_MAX_INPUT_MAPS;
    int maxKernelHeight=CONVOlUTIONAL_RELU_LAYER_MAX_KERNEL_HEIGHT;
    int maxKernelWidth=CONVOlUTIONAL_RELU_LAYER_MAX_KERNEL_WIDTH;
    int maxStrideHeight=CONVOlUTIONAL_RELU_LAYER_MAX_STRIDE_HEIGHT;
    int maxStrideWidth=CONVOlUTIONAL_RELU_LAYER_MAX_STRIDE_WIDTH;
    int maxOutputMaps=CONVOlUTIONAL_RELU_LAYER_MAX_OUTPUT_MAPS;

    int batchSize=util->getRandomIntValue(1, maxBatchSize);
    int inputMaps=util->getRandomIntValue(1, maxInputMaps);
    int outputMaps=util->getRandomIntValue(1, maxOutputMaps);
    float learningRate=(float)(util->getRandomIntValue(1,100))/100.0;
    int inputHeight;
    int outputHeight;
    int kernelHeight;
    int strideHeight;
    do{
        outputHeight=util->getRandomIntValue(1, maxInputHeight);
        kernelHeight=util->getRandomIntValue(1, maxKernelHeight);
        strideHeight=util->getRandomIntValue(1, maxStrideHeight);

        inputHeight=(outputHeight-1)*strideHeight+kernelHeight;
    }while(inputHeight>maxInputHeight);

    int inputWidth;
    int outputWidth;
    int kernelWidth;
    int strideWidth;
    do{
        outputWidth=util->getRandomIntValue(1, maxInputWidth);
        kernelWidth=util->getRandomIntValue(1, maxKernelWidth);
        strideWidth=util->getRandomIntValue(1, maxStrideWidth);

        inputWidth=(outputWidth-1)*strideWidth+kernelWidth;
    }while(inputWidth>maxInputWidth);

    int length=batchSize*inputMaps*inputHeight*inputWidth;
    float* inputValues=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(inputValues, length);

    length=batchSize*outputMaps*outputHeight*outputWidth;
    float* outputErrors=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(outputErrors, length);

    length=outputMaps;
    float* biases=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(biases, length);

    length=outputMaps*inputMaps*kernelHeight*kernelWidth;
    float* weights=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(weights, length);

    convReluLayerCont->batchSize=batchSize;
    convReluLayerCont->inputMaps=inputMaps;
    convReluLayerCont->inputHeight=inputHeight;
    convReluLayerCont->outputMaps=outputMaps;
    convReluLayerCont->outputHeight=outputHeight;
    convReluLayerCont->kernelHeight=kernelHeight;
    convReluLayerCont->strideHeight=strideHeight;
    convReluLayerCont->inputWidth=inputWidth;
    convReluLayerCont->outputWidth=outputWidth;
    convReluLayerCont->kernelWidth=kernelWidth;
    convReluLayerCont->strideWidth=strideWidth;
    convReluLayerCont->inputValues=inputValues;
    convReluLayerCont->outputErrors=outputErrors;
    convReluLayerCont->weights=weights;
    convReluLayerCont->biases=biases;
    convReluLayerCont->learningRate=learningRate;
}

void TestRelu::createConvReluLayerOpennn(ConvReluLayerCont* convReluLayerCont, ConvolutionalLayer* convReluLayerOpennn){
    convReluLayerOpennn->set_row_stride(convReluLayerCont->strideHeight);
    convReluLayerOpennn->set_column_stride(convReluLayerCont->strideWidth);
    convReluLayerOpennn->set_padding_option(ConvolutionalLayer::PaddingOption::NoPadding);
    convReluLayerOpennn->set_activation_function(ConvolutionalLayer::ActivationFunction::RectifiedLinear);

    Vector<double>biases(convReluLayerCont->outputMaps);
    for(int i=0;i<convReluLayerCont->outputMaps;i++)    biases[i]=convReluLayerCont->biases[i];
    convReluLayerOpennn->set_biases(biases);

    Tensor<double>weights(convReluLayerCont->outputMaps,convReluLayerCont->inputMaps,convReluLayerCont->kernelHeight,convReluLayerCont->kernelWidth);
    for(int outMap=0;outMap<convReluLayerCont->outputMaps;outMap++){
        for(int inMap=0;inMap<convReluLayerCont->inputMaps;inMap++){
            for(int yKernel=0;yKernel<convReluLayerCont->kernelHeight;yKernel++){
                for(int xKernel=0;xKernel<convReluLayerCont->kernelWidth;xKernel++){
                    int index=xKernel+convReluLayerCont->kernelWidth*(yKernel+convReluLayerCont->kernelHeight*(inMap+convReluLayerCont->inputMaps*(outMap)));
                    weights(outMap,inMap,yKernel,xKernel)=convReluLayerCont->weights[index];
                }
            }
        }
    }
    convReluLayerOpennn->set_synaptic_weights(weights);
}

int TestRelu::testFeedForward(){
    ConvReluLayerCont* convReluLayerCont=new ConvReluLayerCont();
    createRandomConvReluLayerCont(convReluLayerCont);

    vector<size_t>inputDimension={(size_t)(convReluLayerCont->inputMaps),(size_t)(convReluLayerCont->inputHeight),(size_t)(convReluLayerCont->inputWidth)};   //inputsMaps, inputHeight, inputWidth
    vector<size_t>filterDimension={(size_t)(convReluLayerCont->outputMaps),(size_t)(convReluLayerCont->kernelHeight),(size_t)(convReluLayerCont->kernelWidth)};
    ConvolutionalLayer* convReluLayerOpennn=new ConvolutionalLayer(inputDimension, filterDimension);
    createConvReluLayerOpennn(convReluLayerCont, convReluLayerOpennn);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayerConv=openclLayerCreator->createConvLayer(env, convReluLayerCont->batchSize, convReluLayerCont->inputMaps, convReluLayerCont->inputHeight, convReluLayerCont->inputWidth, convReluLayerCont->outputMaps, convReluLayerCont->outputHeight, convReluLayerCont->outputWidth, convReluLayerCont->kernelHeight, convReluLayerCont->kernelWidth, convReluLayerCont->strideHeight, convReluLayerCont->strideWidth);
    openclLayerConv->setLearningRate(convReluLayerCont->learningRate);
    openclLayerConv->setBiases(env, convReluLayerCont->biases, convReluLayerCont->outputMaps);
    openclLayerConv->setWeights(env, convReluLayerCont->weights, convReluLayerCont->outputMaps*convReluLayerCont->inputMaps*convReluLayerCont->kernelHeight*convReluLayerCont->kernelWidth);
    openclLayerConv->setInputs(env, convReluLayerCont->inputValues, convReluLayerCont->batchSize*convReluLayerCont->inputMaps*convReluLayerCont->inputHeight*convReluLayerCont->inputWidth);

    OpenCLLayer* openclLayerRelu=openclLayerCreator->createReluLayer(env, convReluLayerCont->batchSize, convReluLayerCont->outputMaps, convReluLayerCont->outputHeight, convReluLayerCont->outputWidth);

    openclLayerRelu->setPreviousOpenCLLayer(openclLayerConv);

    //set inputs
    Tensor<double>inputs(convReluLayerCont->batchSize, convReluLayerCont->inputMaps, convReluLayerCont->inputHeight, convReluLayerCont->inputWidth);
    int i=0;
    for(int batch=0;batch<convReluLayerCont->batchSize;batch++){
        for(int map=0;map<convReluLayerCont->inputMaps;map++){
            for(int y=0;y<convReluLayerCont->inputHeight;y++){
                for(int x=0;x<convReluLayerCont->inputWidth;x++){
                    inputs(batch, map, y, x)=convReluLayerCont->inputValues[i];
                    i++;
                }
            }
        }
    }

    //calculate outputs
    Tensor<double>outputs1=convReluLayerOpennn->calculate_outputs(inputs);
    openclLayerConv->computeForward(env, convReluLayerCont->batchSize, convReluLayerCont->outputMaps);
    openclLayerRelu->computeForward(env, convReluLayerCont->batchSize, convReluLayerCont->outputMaps);
    float*outputs2=openclLayerRelu->getOutputs(env, convReluLayerCont->batchSize, convReluLayerCont->outputMaps, convReluLayerCont->outputHeight, convReluLayerCont->outputWidth, NULL);



    //compare outputs
    int differences=0;

    for(int batch=0;batch<convReluLayerCont->batchSize;batch++){
        for(int map=0;map<convReluLayerCont->outputMaps;map++){
            for(int y=0;y<convReluLayerCont->outputHeight;y++){
                for(int x=0;x<convReluLayerCont->outputWidth;x++){
                    int index=x+convReluLayerCont->outputWidth*(y+convReluLayerCont->outputHeight*(map+convReluLayerCont->outputMaps*(batch)));

                    float value1=outputs1(batch, map, y, x);
                    float value2=outputs2[index];

                    float diff=abs(value1-value2);
                    float maxAbsoluteDiff=CONVOlUTIONAL_RELU_LAYER_MAX_ABSOLUTE_DIFFERENCE;
                    if(diff>maxAbsoluteDiff){
                        differences++;
                    }
                }
            }
        }
    }

    delete env;
    delete envCreator;
    delete openclLayerCreator;
    delete openclLayerConv;
    delete openclLayerRelu;
    delete convReluLayerOpennn;
    delete outputs2;
    delete convReluLayerCont;

    return differences;
}

int TestRelu::testErrorComp(){
    ConvReluLayerCont* reluLayerCont=new ConvReluLayerCont();
    createRandomConvReluLayerCont(reluLayerCont);

    int batchSize=reluLayerCont->batchSize;
    int outputMaps=reluLayerCont->outputMaps;
    int outputHeight=reluLayerCont->outputHeight;
    int outputWidth=reluLayerCont->outputWidth;
    float*outputErrors=reluLayerCont->outputErrors;
    int length=batchSize*outputMaps*outputHeight*outputWidth;
    float* inputValues=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(inputValues, length);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createReluLayer(env, batchSize, outputMaps, outputHeight, outputWidth);
    openclLayer->setInputs(env, inputValues, length);
    openclLayer->setOutputErrors(env, outputErrors, length);

    //calculate outputs
    openclLayer->computeForward(env, batchSize, outputMaps);
    openclLayer->computeErrorComp(env, batchSize);
    float*errorInputs=openclLayer->getErrorInputs(env, batchSize, outputMaps, outputHeight, outputWidth, NULL);

    //compare outputs
    int differences=0;

    for(int batch=0;batch<batchSize;batch++){
        for(int map=0;map<outputMaps;map++){
            for(int y=0;y<outputHeight;y++){
                for(int x=0;x<outputWidth;x++){
                    int index=x+outputWidth*(y+outputHeight*(map+outputMaps*(batch)));

                    float inputValue=inputValues[index];
                    float errorInput=errorInputs[index];
                    float errorOutput=outputErrors[index];

                    if(inputValue<=0){
                        if(errorInput!=0){
                            differences++;
                        }
                    }else{
                        float maxAbsoluteDiff=CONVOlUTIONAL_RELU_LAYER_MAX_ABSOLUTE_DIFFERENCE;
                        if(abs(errorOutput-errorInput)>maxAbsoluteDiff){
                            differences++;
                        }
                    }
                }
            }
        }
    }

    delete env;
    delete envCreator;
    delete openclLayerCreator;
    delete openclLayer;
    delete errorInputs;

    return differences;
}

TEST(Relu, FeedforwardProcess){
    TestRelu* p=new TestRelu();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(Relu, ErrorComp){
    TestRelu* p=new TestRelu();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testErrorComp());
    }

    delete p;
}
