#include "Tests/TestsOpenCL/TestConvolutional.hpp"

#include "ie_builders.hpp"
#include "ie_network.hpp"
#include "ie_iexecutable_network.hpp"
#include <iostream>
#include "ie_core.hpp"
#include "Tests/TestsOpenCL/ManuelTestData.hpp"

using namespace std;

#define TEST_CASES 10;

//Convolutional Layer
#define CONVOlUTIONAL_LAYER_MAX_BATCH_SIZE 10;
#define CONVOlUTIONAL_LAYER_MAX_INPUT_HEIGHT 30;
#define CONVOlUTIONAL_LAYER_MAX_INPUT_WIDTH 30;
#define CONVOlUTIONAL_LAYER_MAX_INPUT_MAPS 10;
#define CONVOlUTIONAL_LAYER_MAX_OUTPUT_MAPS 10;
#define CONVOlUTIONAL_LAYER_MAX_KERNEL_HEIGHT 8;
#define CONVOlUTIONAL_LAYER_MAX_KERNEL_WIDTH 8;
#define CONVOlUTIONAL_LAYER_MAX_STRIDE_HEIGHT 8;
#define CONVOlUTIONAL_LAYER_MAX_STRIDE_WIDTH 8;
#define CONVOlUTIONAL_LAYER_MAX_ABSOLUTE_DIFFERENCE 0.0001;

void TestConvolutional::parseStructure(ConvLayerCont* convLayerCont, string content){
    stringstream in(content);
    while(!in.eof()){
        string key;
        in>>key;
        string value;
        in>>value;
        if(key=="BatchSize"){
            convLayerCont->batchSize=stof(value);
        }else if(key=="InputMaps"){
            convLayerCont->inputMaps=stof(value);
        }else if(key=="InputWidth"){
            convLayerCont->inputWidth=stof(value);
        }else if(key=="InputHeight"){
            convLayerCont->inputHeight=stof(value);
        }else if(key=="KernelHeight"){
            convLayerCont->kernelHeight=stof(value);
        }else if(key=="KernelWidth"){
            convLayerCont->kernelWidth=stof(value);
        }else if(key=="StrideHeight"){
            convLayerCont->strideHeight=stof(value);
        }else if(key=="StrideWidth"){
            convLayerCont->strideWidth=stof(value);
        }else if(key=="OutputHeight"){
            convLayerCont->outputHeight=stof(value);
        }else if(key=="OutputWidth"){
            convLayerCont->outputWidth=stof(value);
        }else if(key=="OutputMaps"){
            convLayerCont->outputMaps=stof(value);
        }else{
            cerr<<"This key is not implemented (key,value)!"<<endl;
        }
    }
}

void TestConvolutional::createRandomConvLayerCont(ConvLayerCont* convLayerCont){
    //create parameters
    int maxBatchSize=CONVOlUTIONAL_LAYER_MAX_BATCH_SIZE;
    int maxInputHeight=CONVOlUTIONAL_LAYER_MAX_INPUT_HEIGHT;
    int maxInputWidth=CONVOlUTIONAL_LAYER_MAX_INPUT_WIDTH;
    int maxInputMaps=CONVOlUTIONAL_LAYER_MAX_INPUT_MAPS;
    int maxKernelHeight=CONVOlUTIONAL_LAYER_MAX_KERNEL_HEIGHT;
    int maxKernelWidth=CONVOlUTIONAL_LAYER_MAX_KERNEL_WIDTH;
    int maxStrideHeight=CONVOlUTIONAL_LAYER_MAX_STRIDE_HEIGHT;
    int maxStrideWidth=CONVOlUTIONAL_LAYER_MAX_STRIDE_WIDTH;
    int maxOutputMaps=CONVOlUTIONAL_LAYER_MAX_OUTPUT_MAPS;

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

    length=batchSize*inputMaps*outputHeight*outputWidth;
    float* outputErrors=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(outputErrors, length);

    length=outputMaps;
    float* biases=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(biases, length);

    length=outputMaps*inputMaps*kernelHeight*kernelWidth;
    float* weights=(float*)malloc(sizeof(float)*length);
    util->createRandomValues(weights, length);

    convLayerCont->batchSize=batchSize;
    convLayerCont->inputMaps=inputMaps;
    convLayerCont->inputHeight=inputHeight;
    convLayerCont->outputMaps=outputMaps;
    convLayerCont->outputHeight=outputHeight;
    convLayerCont->kernelHeight=kernelHeight;
    convLayerCont->strideHeight=strideHeight;
    convLayerCont->inputWidth=inputWidth;
    convLayerCont->outputWidth=outputWidth;
    convLayerCont->kernelWidth=kernelWidth;
    convLayerCont->strideWidth=strideWidth;
    convLayerCont->inputValues=inputValues;
    convLayerCont->outputErrors=outputErrors;
    convLayerCont->weights=weights;
    convLayerCont->biases=biases;
    convLayerCont->learningRate=learningRate;
}

void TestConvolutional::createConvLayerOpennn(ConvLayerCont* convLayerCont, ConvolutionalLayer* convLayerOpennn){
    convLayerOpennn->set_row_stride(convLayerCont->strideHeight);
    convLayerOpennn->set_column_stride(convLayerCont->strideWidth);
    convLayerOpennn->set_padding_option(ConvolutionalLayer::PaddingOption::NoPadding);
    convLayerOpennn->set_activation_function(ConvolutionalLayer::ActivationFunction::Linear);

    Vector<double>biases(convLayerCont->outputMaps);
    for(int i=0;i<convLayerCont->outputMaps;i++)    biases[i]=convLayerCont->biases[i];
    convLayerOpennn->set_biases(biases);

    Tensor<double>weights(convLayerCont->outputMaps,convLayerCont->inputMaps,convLayerCont->kernelHeight,convLayerCont->kernelWidth);
    for(int outMap=0;outMap<convLayerCont->outputMaps;outMap++){
        for(int inMap=0;inMap<convLayerCont->inputMaps;inMap++){
            for(int yKernel=0;yKernel<convLayerCont->kernelHeight;yKernel++){
                for(int xKernel=0;xKernel<convLayerCont->kernelWidth;xKernel++){
                    int index=xKernel+convLayerCont->kernelWidth*(yKernel+convLayerCont->kernelHeight*(inMap+convLayerCont->inputMaps*(outMap)));
                    weights(outMap,inMap,yKernel,xKernel)=convLayerCont->weights[index];
                }
            }
        }
    }
    convLayerOpennn->set_synaptic_weights(weights);
}

int TestConvolutional::testFeedForward(){
    ConvLayerCont* convLayerCont=new ConvLayerCont();
    createRandomConvLayerCont(convLayerCont);

    vector<size_t>inputDimension={(size_t)(convLayerCont->inputMaps),(size_t)(convLayerCont->inputHeight),(size_t)(convLayerCont->inputWidth)};   //inputsMaps, inputHeight, inputWidth
    vector<size_t>filterDimension={(size_t)(convLayerCont->outputMaps),(size_t)(convLayerCont->kernelHeight),(size_t)(convLayerCont->kernelWidth)};
    ConvolutionalLayer* convLayerOpennn=new ConvolutionalLayer(inputDimension, filterDimension);
    createConvLayerOpennn(convLayerCont, convLayerOpennn);

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createConvLayer(env, convLayerCont->batchSize, convLayerCont->inputMaps, convLayerCont->inputHeight, convLayerCont->inputWidth, convLayerCont->outputMaps, convLayerCont->outputHeight, convLayerCont->outputWidth, convLayerCont->kernelHeight, convLayerCont->kernelWidth, convLayerCont->strideHeight, convLayerCont->strideWidth);
    openclLayer->setLearningRate(convLayerCont->learningRate);
    openclLayer->setBiases(env, convLayerCont->biases, convLayerCont->outputMaps);
    openclLayer->setWeights(env, convLayerCont->weights, convLayerCont->outputMaps*convLayerCont->inputMaps*convLayerCont->kernelHeight*convLayerCont->kernelWidth);
    openclLayer->setInputs(env, convLayerCont->inputValues, convLayerCont->batchSize*convLayerCont->inputMaps*convLayerCont->inputHeight*convLayerCont->inputWidth);

    //set inputs
    Tensor<double>inputs(convLayerCont->batchSize, convLayerCont->inputMaps, convLayerCont->inputHeight, convLayerCont->inputWidth);
    int i=0;
    for(int batch=0;batch<convLayerCont->batchSize;batch++){
        for(int map=0;map<convLayerCont->inputMaps;map++){
            for(int y=0;y<convLayerCont->inputHeight;y++){
                for(int x=0;x<convLayerCont->inputWidth;x++){
                    inputs(batch, map, y, x)=convLayerCont->inputValues[i];
                    i++;
                }
            }
        }
    }

    //calculate outputs
    Tensor<double>outputs1=convLayerOpennn->calculate_outputs(inputs);
    openclLayer->computeForward(env, convLayerCont->batchSize, convLayerCont->outputMaps);
    float*outputs2=openclLayer->getOutputs(env, convLayerCont->batchSize, convLayerCont->outputMaps, convLayerCont->outputHeight, convLayerCont->outputWidth, NULL);



    //compare outputs
    int differences=0;

    for(int batch=0;batch<convLayerCont->batchSize;batch++){
        for(int map=0;map<convLayerCont->outputMaps;map++){
            for(int y=0;y<convLayerCont->outputHeight;y++){
                for(int x=0;x<convLayerCont->outputWidth;x++){
                    int index=x+convLayerCont->outputWidth*(y+convLayerCont->outputHeight*(map+convLayerCont->outputMaps*(batch)));

                    float value1=outputs1(batch, map, y, x);
                    float value2=outputs2[index];

                    float diff=abs(value1-value2);
                    float maxAbsoluteDiff=CONVOlUTIONAL_LAYER_MAX_ABSOLUTE_DIFFERENCE;
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
    delete openclLayer;
    delete convLayerOpennn;
    delete outputs2;
    delete convLayerCont;

    return differences;
}

int TestConvolutional::testErrorComp(){
    ManuelTestData* manuelTestData=new ManuelTestData();

    //load errors input
    vector<float>vectorErrorsInput;
    util->loadStringToArray(manuelTestData->getConvErrorsInputTest1(),&vectorErrorsInput);
    float*errorsInput=(float*)malloc(sizeof(float)*vectorErrorsInput.size());
    util->convertVectorToFloatArray(&vectorErrorsInput, errorsInput);

    //load errors output
    vector<float>vectorErrorsOutput;
    util->loadStringToArray(manuelTestData->getConvErrorsOutputTest1(),&vectorErrorsOutput);
    float*errorsOutput=(float*)malloc(sizeof(float)*vectorErrorsOutput.size());
    util->convertVectorToFloatArray(&vectorErrorsOutput, errorsOutput);

    //load input values
    vector<float>vectorInputValues;
    util->loadStringToArray(manuelTestData->getConvInputValuesTest1(),&vectorInputValues);
    float*inputValues=(float*)malloc(sizeof(float)*vectorInputValues.size());
    util->convertVectorToFloatArray(&vectorInputValues, inputValues);

    //load output values
    vector<float>vectorOutputValues;
    util->loadStringToArray(manuelTestData->getConvOutputValuesTest1(),&vectorOutputValues);
    float*outputValues=(float*)malloc(sizeof(float)*vectorOutputValues.size());
    util->convertVectorToFloatArray(&vectorOutputValues, outputValues);

    //load weight values
    vector<float>vectorWeightValues;
    util->loadStringToArray(manuelTestData->getConvWeightsTest1(),&vectorWeightValues);
    float*weightValues=(float*)malloc(sizeof(float)*vectorWeightValues.size());
    util->convertVectorToFloatArray(&vectorWeightValues, weightValues);

    //load bias values
    vector<float>vectorBiasValues;
    util->loadStringToArray(manuelTestData->getConvBiasesTest1(),&vectorBiasValues);
    float*biasValues=(float*)malloc(sizeof(float)*vectorBiasValues.size());
    util->convertVectorToFloatArray(&vectorBiasValues, biasValues);

    string content=manuelTestData->getConvStructureTest1();
    ConvLayerCont* convLayerCont=new ConvLayerCont();
    parseStructure(convLayerCont, content);
    convLayerCont->outputErrors=errorsOutput;
    convLayerCont->inputValues=inputValues;
    convLayerCont->weights=weightValues;
    convLayerCont->biases=biasValues;

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createConvLayer(env, convLayerCont->batchSize, convLayerCont->inputMaps, convLayerCont->inputHeight, convLayerCont->inputWidth, convLayerCont->outputMaps, convLayerCont->outputHeight, convLayerCont->outputWidth, convLayerCont->kernelHeight, convLayerCont->kernelWidth, convLayerCont->strideHeight, convLayerCont->strideWidth);
    openclLayer->setInputs(env, convLayerCont->inputValues, convLayerCont->batchSize*convLayerCont->inputMaps*convLayerCont->inputHeight*convLayerCont->inputWidth);
    openclLayer->setOutputErrors(env, convLayerCont->outputErrors, convLayerCont->batchSize*convLayerCont->outputMaps*convLayerCont->outputHeight*convLayerCont->outputWidth);
    openclLayer->setBiases(env, convLayerCont->biases, convLayerCont->outputMaps);
    openclLayer->setWeights(env, convLayerCont->weights, convLayerCont->outputMaps*convLayerCont->inputMaps*convLayerCont->kernelHeight*convLayerCont->kernelWidth);

    openclLayer->computeForward(env, convLayerCont->batchSize, convLayerCont->outputMaps);
    openclLayer->computeErrorComp(env, convLayerCont->batchSize);
    float*computedInputErrors=openclLayer->getErrorInputs(env, convLayerCont->batchSize, convLayerCont->inputMaps, convLayerCont->inputHeight, convLayerCont->inputWidth, NULL);

    int differences=0;
    for(int batch=0;batch<convLayerCont->batchSize;batch++){
        for(int map=0;map<convLayerCont->inputMaps;map++){
            for(int y=0;y<convLayerCont->inputHeight;y++){
                for(int x=0;x<convLayerCont->inputWidth;x++){
                    int index=x+convLayerCont->inputWidth*(y+convLayerCont->inputHeight*(map+convLayerCont->inputMaps*(batch)));
                    float diff=errorsInput[index]-computedInputErrors[index];
                    float maxAbsolutDifference=CONVOlUTIONAL_LAYER_MAX_ABSOLUTE_DIFFERENCE;
                    if(abs(diff)>maxAbsolutDifference){
                        differences++;
                        cout<<errorsInput[index]<<"\t\t"<<computedInputErrors[index]<<"\t"<<batch<<"\t"<<map<<"\t"<<y<<"\t"<<x<<endl;
                    }
                }
            }
        }
    }

    delete[]computedInputErrors;
    delete envCreator;
    delete env;
    delete openclLayerCreator;
    delete openclLayer;
    delete convLayerCont;
    delete[]errorsInput;
    delete[]outputValues;
    delete manuelTestData;

    return differences;
}

int TestConvolutional::testWeightsUpdate(){
    ManuelTestData* manuelTestData=new ManuelTestData();

    //load errors input
    vector<float>vectorErrorsInput;
    util->loadStringToArray(manuelTestData->getConvErrorsInputTest1(),&vectorErrorsInput);
    float*errorsInput=(float*)malloc(sizeof(float)*vectorErrorsInput.size());
    util->convertVectorToFloatArray(&vectorErrorsInput, errorsInput);

    //load errors output
    vector<float>vectorErrorsOutput;
    util->loadStringToArray(manuelTestData->getConvErrorsOutputTest1(),&vectorErrorsOutput);
    float*errorsOutput=(float*)malloc(sizeof(float)*vectorErrorsOutput.size());
    util->convertVectorToFloatArray(&vectorErrorsOutput, errorsOutput);

    //load input values
    vector<float>vectorInputValues;
    util->loadStringToArray(manuelTestData->getConvInputValuesTest1(),&vectorInputValues);
    float*inputValues=(float*)malloc(sizeof(float)*vectorInputValues.size());
    util->convertVectorToFloatArray(&vectorInputValues, inputValues);

    //load output values
    vector<float>vectorOutputValues;
    util->loadStringToArray(manuelTestData->getConvOutputValuesTest1(),&vectorOutputValues);
    float*outputValues=(float*)malloc(sizeof(float)*vectorOutputValues.size());
    util->convertVectorToFloatArray(&vectorOutputValues, outputValues);

    //load weight values
    vector<float>vectorWeightValues;
    util->loadStringToArray(manuelTestData->getConvWeightsTest1(),&vectorWeightValues);
    float*weightValues=(float*)malloc(sizeof(float)*vectorWeightValues.size());
    util->convertVectorToFloatArray(&vectorWeightValues, weightValues);

    //load bias values
    vector<float>vectorBiasValues;
    util->loadStringToArray(manuelTestData->getConvBiasesTest1(),&vectorBiasValues);
    float*biasValues=(float*)malloc(sizeof(float)*vectorBiasValues.size());
    util->convertVectorToFloatArray(&vectorBiasValues, biasValues);

    //load new bias values
    vector<float>vectorNewBiasValues;
    util->loadStringToArray(manuelTestData->getConvNewBiasesTest1(),&vectorNewBiasValues);
    float*newBiasValues=(float*)malloc(sizeof(float)*vectorNewBiasValues.size());
    util->convertVectorToFloatArray(&vectorNewBiasValues, newBiasValues);

    //load new weight values
    vector<float>vectorNewWeightValues;
    util->loadStringToArray(manuelTestData->getConvNewWeightsTest1(),&vectorNewWeightValues);
    float*newWeightValues=(float*)malloc(sizeof(float)*vectorNewWeightValues.size());
    util->convertVectorToFloatArray(&vectorNewWeightValues, newWeightValues);

    //load learning rate
    float learningRate=stof(manuelTestData->getConvLearningRateTest1());

    string content=manuelTestData->getConvStructureTest1();
    ConvLayerCont* convLayerCont=new ConvLayerCont();
    parseStructure(convLayerCont, content);
    convLayerCont->outputErrors=errorsOutput;
    convLayerCont->inputValues=inputValues;
    convLayerCont->weights=weightValues;
    convLayerCont->biases=biasValues;
    convLayerCont->learningRate=learningRate;

    OpenCLEnvironmentCreator* envCreator=new OpenCLEnvironmentCreator();
    OpenCLEnvironment* env=envCreator->createOpenCLEnvironment(HardwareType::CPU);
    OpenCLLayerCreator* openclLayerCreator=new OpenCLLayerCreator();
    OpenCLLayer* openclLayer=openclLayerCreator->createConvLayer(env, convLayerCont->batchSize, convLayerCont->inputMaps, convLayerCont->inputHeight, convLayerCont->inputWidth, convLayerCont->outputMaps, convLayerCont->outputHeight, convLayerCont->outputWidth, convLayerCont->kernelHeight, convLayerCont->kernelWidth, convLayerCont->strideHeight, convLayerCont->strideWidth);
    openclLayer->setInputs(env, convLayerCont->inputValues, convLayerCont->batchSize*convLayerCont->inputMaps*convLayerCont->inputHeight*convLayerCont->inputWidth);
    openclLayer->setOutputErrors(env, convLayerCont->outputErrors, convLayerCont->batchSize*convLayerCont->outputMaps*convLayerCont->outputHeight*convLayerCont->outputWidth);
    openclLayer->setBiases(env, convLayerCont->biases, convLayerCont->outputMaps);
    openclLayer->setWeights(env, convLayerCont->weights, convLayerCont->outputMaps*convLayerCont->inputMaps*convLayerCont->kernelHeight*convLayerCont->kernelWidth);
    openclLayer->setLearningRate(convLayerCont->learningRate);

    openclLayer->computeForward(env, convLayerCont->batchSize, convLayerCont->outputMaps);
    openclLayer->computeErrorComp(env, convLayerCont->batchSize);
    openclLayer->computeWeightsUpdate(env, convLayerCont->outputMaps);
    float*computedNewBiases=openclLayer->getBiases(env, convLayerCont->outputMaps);
    float*computedNewWeights=openclLayer->getWeights(env, convLayerCont->outputMaps*convLayerCont->inputMaps*convLayerCont->kernelHeight*convLayerCont->kernelWidth);

    int differences=0;
    float maxAbsolutDifference=CONVOlUTIONAL_LAYER_MAX_ABSOLUTE_DIFFERENCE;
    for(int outMap=0;outMap<convLayerCont->outputMaps;outMap++){
        for(int inMap=0;inMap<convLayerCont->inputMaps;inMap++){
            for(int y=0;y<convLayerCont->kernelHeight;y++){
                for(int x=0;x<convLayerCont->kernelWidth;x++){
                    int index=x+convLayerCont->kernelWidth*(y+convLayerCont->kernelHeight*(inMap+convLayerCont->inputMaps*(outMap)));
                    float diff=computedNewWeights[index]-newWeightValues[index];
                    if(abs(diff)>maxAbsolutDifference){
                        differences++;
                    }
                }
            }
        }
        float diff=computedNewBiases[outMap]-newBiasValues[outMap];
        if(abs(diff)>maxAbsolutDifference){
            differences++;
        }
    }

    delete[]newWeightValues;
    delete[]newBiasValues;
    delete[]computedNewBiases;
    delete[]computedNewWeights;
    delete envCreator;
    delete env;
    delete openclLayerCreator;
    delete openclLayer;
    delete convLayerCont;
    delete[]errorsInput;
    delete[]outputValues;
    delete manuelTestData;

    return differences;
}

TEST(Convolutional, FeedforwardProcess){
    TestConvolutional* p=new TestConvolutional();

    int testCases=TEST_CASES;
    for(int testCase=0;testCase<testCases;testCase++){
        EXPECT_EQ(0,p->testFeedForward());
    }

    delete p;
}

TEST(Convolutional, ErrorComp){
    TestConvolutional* p=new TestConvolutional();

    EXPECT_EQ(0,p->testErrorComp());

    delete p;
}

TEST(Convolutional, WeightsUpdate){
    TestConvolutional* p=new TestConvolutional();

    EXPECT_EQ(0,p->testWeightsUpdate());

    delete p;
}
